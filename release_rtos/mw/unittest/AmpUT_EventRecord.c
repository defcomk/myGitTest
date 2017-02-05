/**
 *  @file AmpUT_EventRecord.c
 *
 *  **History**
 *      |Date       |Name        |Comments       |
 *      |-----------|------------|---------------|
 *      |2013/11/01 |clchan      |Created        |
 *
 *
 *  @copyright 2013 Ambarella Corporation. All rights reserved.
 *                 No part of this file may be reproduced, stored in a retrieval system,
 *                 or transmitted, in any form, or by any means, electronic, mechanical, photocopying,
 *                 recording, or otherwise, without the prior consent of Ambarella Corporation.
 */

#include <recorder/Encode.h>
#include "AmpUnitTest.h"
#include "AmbaUtility.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <AmbaCache_Def.h>
#include "DummyVideoEnc.h"
#include "FormatLib.h"

#include <format/Muxer.h>
#include "PrecMux.h"
#include <format/Mp4Mux.h>
#include <index/Index.h>
#include <index/Temp.h>
#include <stream/File.h>
#include <util.h>

#define USE_PREC_MUX /**< event record method */

#define BS_FN   "C:\\OUT_0000.h264" /**< H264 bitstream file name */
#define HDR_FN  "C:\\OUT_0000.nhnt" /**< nhnt file name */
#define UDTA_FN "C:\\OUT_0000.udta" /**< user define data file name */
#define MP4_FN_PREFIX   "C:\\TEST" /**< prefix of the split file */
#define EVTREC_CODEC_HDLR ((void *)0x1234) /**< codec handler */
#define EVTREC_ENC_RAW_SIZE (24 << 20) /**< 12MB raw buffer */
#define EVTREC_MAX_FIFO_NUM 1024    /**< at least event length */
#define EVENT_PREC_LENGTH   (1000 * 3)  /**< 3 second pre-record */
#define EVENT_LENGTH        (1000 * 13) /**< 13 second event */
#define STACK_SIZE  0x4000 /**< stack size */

/**
 * Macro - DTS to Time
 */
#define AMP_FORMAT_DTS_TO_TIME(DTS, TimeScale)    (((UINT64)(DTS) / (TimeScale)) * 1000 + (((UINT64)(DTS) % (TimeScale)) * 1000) / (TimeScale))

static void *g_pEncBuffer = NULL; /**< mux buffer */
static AMP_FIFO_HDLR_s *g_pEncFifoHdlr = NULL; /**< encode FIFO handler */
static AMP_FIFO_HDLR_s *g_pMuxFifoHdlr = NULL; /**< mux FIFO handler */
static AMP_STREAM_HDLR_s *g_pStream = NULL; /**< stream handler */
static AMP_INDEX_HDLR_s *g_pIndex = NULL; /**< index handler */
static AMP_MOVIE_INFO_s *g_pMovie = NULL; /**< movie information */
static AMP_MUXER_PIPE_HDLR_s *g_pMuxPipe = NULL; /**< muxer pipe */
static AMP_MUX_FORMAT_HDLR_s *g_pMp4Mux = NULL; /**< format handler */

static AMBA_KAL_TASK_t g_MuxTask = {0}; /**< mux task */
static void *g_pMuxStack = NULL; /**< mux stack */

static UINT32 g_nEventCount = 0; /**< count of evnet */
static FORMAT_USER_DATA_s g_Udta; /**< user define data */
static DummyVideoEnc_s g_Encoder; /**< video encoder */

#ifdef USE_PREC_MUX
static AMP_MUX_FORMAT_HDLR_s *g_pPrecMux = NULL; /**< format handler */
#endif


/**
 * Event record UT - video encoder event callback function.
 *
 * @param [in] pHdlr video encoder handler.
 * @param [in] nEvent event id.
 * @param [in] pInfo callback information.
 * @return 0 - OK, others - fail
 *
 */
static int DummyVideoEnc_EventCB(void *pHdlr, UINT32 nEvent, void *pInfo)
{
//    AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    if (nEvent == AMP_FIFO_EVENT_DATA_CONSUMED) {
        if (RingBuf_DeleteFrame(&g_Encoder.RingBuf) == -1)
             AmbaPrint("RingBuf_DeleteFrame Fail");
    }

    return 0;
}

/**
 * Event record UT - create movie name function.
 *
 * @param [out] szName movie name.
 * @param [in] nSize length of movie name.
 *
 */
static void AmpUT_EventRecord_CreateMovName(char *szName, UINT32 nSize)
{
    char file[MAX_FILENAME_LENGTH] = {0};
    snprintf(file, MAX_FILENAME_LENGTH, "%s%02u.MP4", MP4_FN_PREFIX, g_nEventCount);
    strncpy(szName, file, nSize);
    szName[nSize - 1] = '\0';
    g_nEventCount++;
}

#ifdef USE_PREC_MUX

/**
 * Event record UT - mux task.
 *
 * @param [in] info task information.
 *
 */
static void AmpUT_EventRecord_MuxTask(UINT32 info)
{
    int rval = 0;
    AmbaPrint("%s Start", __FUNCTION__);
    AmpMuxer_WaitComplete(g_pMuxPipe, AMBA_KAL_WAIT_FOREVER);
    if (g_pMuxPipe->Format[0] == g_pMp4Mux) {
        if (g_pStream->Func->Close(g_pStream) != AMP_OK) {
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            rval = -1;
            goto DONE;
        }
    }
    if (AmpMuxer_Remove(g_pMuxPipe) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    if (AmpMuxer_Delete(g_pMuxPipe) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pMuxPipe = NULL;
    if (AmpTempIdx_Delete(g_pIndex) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pIndex = NULL;
    if (AmpFileStream_Delete(g_pStream) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pStream = NULL;
    while (AmpCFS_FStatus(g_pMovie->Name) != AMP_CFS_STATUS_UNUSED)
        AmbaKAL_TaskSleep(100);
    if (AmpMp4Mux_Delete(g_pMp4Mux) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pMp4Mux = NULL;
    if (PrecMux_Delete(g_pPrecMux) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pPrecMux = NULL;
    if (AmpFormat_RelMovieInfo(g_pMovie, TRUE) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        rval = -1;
        goto DONE;
    }
    g_pMovie = NULL;
    if (g_pMuxFifoHdlr != NULL) {
        AmpFifo_Delete(g_pMuxFifoHdlr);
        g_pMuxFifoHdlr = NULL;
    }
    if (g_pEncFifoHdlr != NULL) {
        AmpFifo_Delete(g_pEncFifoHdlr);
        g_pEncFifoHdlr = NULL;
    }
DONE:
    if (rval == -1) {
        AmbaPrint("[FAIL] %s", __FUNCTION__);
    } else {
        AmbaPrint("%s Stop", __FUNCTION__);
        AmbaPrint("[SUCCESS] AmpUT_EventRecord : End");
    }
}

/**
 * Event record UT - FIFO callback function.
 *
 * @param [in] hdlr FIFO handler.
 * @param [in] event event id.
 * @param [in] Info callback information.
 * @return 0 - OK, others - fail
 *
 */
static int  AmpUT_EventRecord_FifoCB(void *hdlr, UINT32 event, void* info)
{
//    AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    if (event == AMP_FIFO_EVENT_DATA_READY) {
        AmpMuxer_OnDataReady((AMP_FIFO_HDLR_s *)hdlr);
    } else if (event == AMP_FIFO_EVENT_DATA_EOS) {
        AmpMuxer_OnEOS((AMP_FIFO_HDLR_s *)hdlr);
    }

    return 0;
}

/**
 * Event record UT - file split function.
 *
 * @param [in,out] pMovie movie information.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_NewSession(AMP_MOVIE_INFO_s *pMovie)
{
    UINT8 TrackId;
    UINT64 nMinDTS;
    AMP_MEDIA_TRACK_INFO_s *pMin;
    if (FormatLib_AdjustDTS(pMovie) != AMP_OK) {
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        return -1;
    }
    pMin = FormatLib_GetShortestTrack((AMP_MEDIA_INFO_s *)pMovie);
    K_ASSERT(pMin != NULL);
    nMinDTS = pMin->DTS;
    for (TrackId = 0; TrackId < pMovie->TrackCount; TrackId++) {
        AMP_MEDIA_TRACK_INFO_s *pTrack = &pMovie->Track[TrackId];
        pTrack->InitDTS = pTrack->NextDTS = pTrack->DTS = (pTrack->DTS - nMinDTS);
        if (pTrack->TrackType == AMP_MEDIA_TRACK_TYPE_VIDEO) {
            pTrack->Info.Video.RefDTS = pTrack->InitDTS;
            FormatLib_ResetPTS(&pMovie->Track[TrackId]);
        }
    }
    return 0;
}

/**
 * Event record UT - change format function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_ChangeFormat(void)
{
    int rval = -1;
    AMP_MOVIE_INFO_s *pMovie;
    char szName[MAX_FILENAME_LENGTH] = {'\0'};
    if (g_pMuxPipe->Format[0] == g_pPrecMux) {
        // prec done, change to MP4
        if (g_pPrecMux->Func->Close(g_pPrecMux, AMP_MUX_FORMAT_CLOSE_DEFAULT) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        AmpUT_EventRecord_CreateMovName(szName, MAX_FILENAME_LENGTH);
        // replace media info
        AmpFormat_NewMovieInfo(szName, &pMovie);
        AmpFormat_CopyMovieInfo(pMovie, g_pMovie);
        AmpFormat_RelMovieInfo(g_pMovie, TRUE);
        g_pMovie = pMovie;
        // split new session
        AmpUT_EventRecord_NewSession(g_pMovie);
        // change to mp4
        if (g_pStream->Func->Open(g_pStream, szName, AMP_STREAM_MODE_WRONLY) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        g_pMp4Mux->Media = (AMP_MEDIA_INFO_s *)g_pMovie;
        g_pMuxPipe->Format[0] = g_pMp4Mux;
        AmpMuxer_SetMaxDuration(g_pMuxPipe, EVENT_LENGTH);
        FormatLib_ResetMuxMediaInfo((AMP_MEDIA_INFO_s *)g_pMovie);
        if (g_pMp4Mux->Func->Open(g_pMp4Mux) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        rval = 0;
    } else {
        // mp4 done, change to prec
        if (g_pMp4Mux->Func->Close(g_pMp4Mux, AMP_MUX_FORMAT_CLOSE_DEFAULT) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        if (g_pStream->Func->Close(g_pStream) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        AmbaPrint("[SUCCESS] %s is closed.", g_pMovie->Name);
        // split new session
        AmpUT_EventRecord_NewSession(g_pMovie);
        // change to prec
        g_pPrecMux->Media = (AMP_MEDIA_INFO_s *)g_pMovie;
        g_pMuxPipe->Format[0] = g_pPrecMux;
        AmpMuxer_SetMaxDuration(g_pMuxPipe, 0xFFFFFFFF);
        FormatLib_ResetMuxMediaInfo((AMP_MEDIA_INFO_s *)g_pMovie);
        if (g_pPrecMux->Func->Open(g_pPrecMux) != AMP_OK)
            AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
        rval = 0;
    }
    return rval;
}

/**
 * Event record UT - mux callback function.
 *
 * @param [in] hdlr muxer handler.
 * @param [in] event event id.
 * @param [in] info callback information.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_MuxCB(void* hdlr, UINT32 event, void* info)
{
    int rval = 0;
    switch (event) {
    case AMP_MUXER_EVENT_START:
        AmbaPrint("AMP_MUXER_EVENT_START");
        break;
    case AMP_MUXER_EVENT_END:
        AmbaPrint("AMP_MUXER_EVENT_END");
        DummyVideoEnc_Stop(&g_Encoder);
        break;
    case AMP_MUXER_EVENT_REACH_LIMIT:
        AmbaPrint("AMP_MUXER_EVENT_REACH_LIMIT");
        rval = AmpUT_EventRecord_ChangeFormat();
        break;
    default:
        AmbaPrint("[FAIL] %s: event = %u", __FUNCTION__, event);
        break;
    }
    return rval;
}

/**
 * Event record UT - event function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_event(void)
{
    if (g_pMuxPipe != NULL) { // actually, g_pMuxPipe should be protected by mutex (to avoid it is released by muxer)
        if (AmpMuxer_LockPipe(g_pMuxPipe) == AMP_OK) {
            if (g_pMuxPipe->Format[0] == g_pPrecMux) {
                AMP_FIFO_INFO_s info;
                AMP_MEDIA_TRACK_INFO_s * const pDefault = &g_pMovie->Track[0]; // from config, track 0 is default video track
                if (AmpFifo_GetInfo(pDefault->Fifo, &info) == AMP_OK) {
                    // set limit at the latest frame
                    const UINT64 dts = pDefault->DTS + info.AvailEntries * (pDefault->TimePerFrame / pDefault->Info.Video.VFR);
                    AmpMuxer_SetMaxDuration(g_pMuxPipe, AMP_FORMAT_DTS_TO_TIME(dts, pDefault->TimeScale));
                } else {
                    AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
                }
            } else {
                AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            }
            AmpMuxer_UnlockPipe(g_pMuxPipe);
        } else {
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        }
    } else {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
    }
    return 0;
}
#else

static UINT32 SystemState = 0; // 0:prec start; 1:event start; 2:event end;

static int AmpUT_EventRecord_Close(void)
{
    AmpMuxer_WaitComplete(g_pMuxPipe, AMBA_KAL_WAIT_FOREVER);
    if (g_pStream->Func->Close(g_pStream) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    if (AmpMuxer_Remove(g_pMuxPipe) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    if (AmpMuxer_Delete(g_pMuxPipe) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    g_pMuxPipe = NULL;
    if (AmpTempIdx_Delete(g_pIndex) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    g_pIndex = NULL;
    if (AmpFileStream_Delete(g_pStream) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    g_pStream = NULL;
    while (AmpCFS_FStatus(g_pMovie->Name) != AMP_CFS_STATUS_UNUSED)
        AmbaKAL_TaskSleep(100);
    if (AmpMp4Mux_Delete(g_pMp4Mux) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    g_pMp4Mux = NULL;
    if (AmpFormat_RelMovieInfo(g_pMovie, TRUE) != AMP_OK)
        AmbaPrint("%s, %d", __FUNCTION__, __LINE__);
    g_pMovie = NULL;
    if (g_pMuxFifoHdlr != NULL) {
        AmpFifo_Delete(g_pMuxFifoHdlr);
        g_pMuxFifoHdlr = NULL;
    }
    SystemState = 0;
    return 0;
}

static void AmpUT_EventRecord_MuxTask(UINT32 info)
{
    AmbaPrint("%s Start", __FUNCTION__);
    while (1) {
        if (SystemState == 2) {
            AmpMuxer_Stop(g_pMuxPipe);
            AmpUT_EventRecord_Close();
        }
        AmbaKAL_TaskSleep(10);
    }
    AmbaPrint("%s Stop", __FUNCTION__);
}

static int  AmpUT_EventRecord_FifoCB(void *hdlr, UINT32 event, void* info)
{
//    AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    if (event == AMP_FIFO_EVENT_DATA_READY && SystemState == 1) {
        AmpMuxer_OnDataReady((AMP_FIFO_HDLR_s *)hdlr);
    } else if (event == AMP_FIFO_EVENT_DATA_EOS) {
        AmpMuxer_OnEOS((AMP_FIFO_HDLR_s *)hdlr);
    }

    return 0;
}

static int AmpUT_EventRecord_MuxCB(void* hdlr, UINT32 event, void* info)
{
    int rval = 0;
    switch (event) {
    case AMP_MUXER_EVENT_START:
        AmbaPrint("AMP_MUXER_EVENT_START");
        break;
    case AMP_MUXER_EVENT_END:
        AmbaPrint("AMP_MUXER_EVENT_END");
        if (SystemState != 2) {
            DummyVideoEnc_Stop(&g_Encoder);
        }
        break;
    case AMP_MUXER_EVENT_REACH_LIMIT:
        AmbaPrint("AMP_MUXER_EVENT_REACH_LIMIT");
        SystemState = 2;
        break;
    default:
        break;
    }
    return rval;
}

static int AmpUT_EventRecord_event(void)
{
    AMP_FIFO_CFG_s fifoDefCfg;
    AMP_MUX_MOVIE_INFO_CFG_s movieCfg;
    AMP_FILE_STREAM_CFG_s fileCfg;
    AMP_TEMP_IDX_CFG_s tempCfg;
    AMP_MP4_MUX_CFG_s mp4Cfg;
    AMP_MUXER_PIPE_CFG_s muxPipeCfg;
    char szName[MAX_FILENAME_LENGTH] = {'\0'};

    // create muxer fifo
    AmpFifo_GetDefaultCfg(&fifoDefCfg);
    fifoDefCfg.hCodec = EVTREC_CODEC_HDLR;
    fifoDefCfg.IsVirtual = 1;
    fifoDefCfg.NumEntries = EVTREC_MAX_FIFO_NUM;
    fifoDefCfg.cbEvent = AmpUT_EventRecord_FifoCB;
    fifoDefCfg.InitData.CreateFifoWithInitData = TRUE;
    fifoDefCfg.InitData.InitCondition = AMP_FIFO_CFG_INIT_WITH_NUM_FRAME; //--
    fifoDefCfg.InitData.InitParam.NumFrame = (g_Udta.nTimeScale * EVENT_PREC_LENGTH / 1000)/g_Udta.nTickPerPicture; //--
    fifoDefCfg.InitData.FristFrameType = AMP_FIFO_TYPE_IDR_FRAME; //--
    AmpFifo_Create(&fifoDefCfg, &g_pMuxFifoHdlr);
    // open media info
    AmpUT_EventRecord_CreateMovName(szName, MAX_FILENAME_LENGTH);
    AmpFormat_NewMovieInfo(szName, &g_pMovie);
    // set media info
    AmpMuxer_GetDefaultMovieInfoCfg(&movieCfg);
    movieCfg.TrackCount = 1;
    movieCfg.Track[0].TrackType = AMP_MEDIA_TRACK_TYPE_VIDEO;
    movieCfg.Track[0].Fifo = g_pMuxFifoHdlr;
    movieCfg.Track[0].BufferBase = (UINT8 *)g_pEncBuffer;
    movieCfg.Track[0].BufferLimit = (UINT8 *)g_pEncBuffer + EVTREC_ENC_RAW_SIZE;
    movieCfg.Track[0].MediaId = AMP_FORMAT_MID_AVC;
    movieCfg.Track[0].TimeScale = g_Udta.nTimeScale;//atoi(Rate);
    movieCfg.Track[0].TimePerFrame = g_Udta.nTickPerPicture;//atoi(Scale);
    movieCfg.Track[0].Info.Video.Mode = AMP_VIDEO_MODE_P;
    movieCfg.Track[0].Info.Video.M = g_Udta.nM;//atoi(M);
    movieCfg.Track[0].Info.Video.N = g_Udta.nN;//atoi(N);
    movieCfg.Track[0].Info.Video.GOPSize = (UINT32)movieCfg.Track[0].Info.Video.N * g_Udta.nIdrInterval;//atoi(idrItvl);
    movieCfg.Track[0].Info.Video.CodecTimeScale = 90000;    // TODO: should remove CodecTimeScale, but the sample clip uses 90K
    movieCfg.Track[0].Info.Video.Width = g_Udta.nVideoWidth;//atoi(Width);
    movieCfg.Track[0].Info.Video.Height = g_Udta.nVideoHeight;//atoi(Height);
    AmpMuxer_InitMovieInfo(g_pMovie, &movieCfg);

    // create file stream
    AmpFileStream_GetDefaultCfg(&fileCfg);
    AmpFileStream_Create(&fileCfg, &g_pStream);
    if (g_pStream->Func->Open(g_pStream, g_pMovie->Name, AMP_STREAM_MODE_WRONLY) != AMP_OK)
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
    // create Index
    AmpTempIdx_GetDefaultCfg(&tempCfg);
    if (AmpTempIdx_Create(&tempCfg, &g_pIndex) != AMP_OK)
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);

    // create Mp4Mux
    AmpMp4Mux_GetDefaultCfg(&mp4Cfg);
    mp4Cfg.Stream = g_pStream;
    mp4Cfg.Index = g_pIndex;
    AmpMp4Mux_Create(&mp4Cfg, &g_pMp4Mux);
    // create muxer pipe
    AmpMuxer_GetDefaultCfg(&muxPipeCfg);
    muxPipeCfg.FormatCount = 1;
    muxPipeCfg.Format[0] = g_pMp4Mux;
    muxPipeCfg.Media[0] = (AMP_MEDIA_INFO_s *)g_pMovie;
    muxPipeCfg.MaxDuration = EVENT_LENGTH;
    muxPipeCfg.OnEvent = AmpUT_EventRecord_MuxCB;
    AmpMuxer_Create(&muxPipeCfg, &g_pMuxPipe);
    AmpMuxer_Add(g_pMuxPipe);
    AmpMuxer_Start(g_pMuxPipe, AMBA_KAL_NO_WAIT);   // muxer should be started before encode start (to avoid missing data ready)
    SystemState = 1;
    AmbaPrint("%s:%s is opened", __FUNCTION__, g_pMovie->Name);
    return 0;
}

#endif

/**
 * Event record UT - initiate function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_init(void)
{
    AMP_FIFO_CFG_s fifoDefCfg;
    AMP_FORMAT_INIT_CFG_s fmtInitCfg;
    void *pFmtBuf = NULL;
    AMP_MUXER_INIT_CFG_s muxerInitCfg;
    void *pMuxerBuf = NULL;
#ifdef USE_PREC_MUX
    PREC_MUX_INIT_CFG_s precInitCfg;
    void *pPrecBuf = NULL;
#endif
    AMP_MP4_MUX_INIT_CFG_s MP4MuxInitCfg;
    void *pMp4Buf = NULL;
    AMP_INDEX_INIT_CFG_s IndexInitCfg;
    void *pIdxBuf = NULL;
    AMP_TEMP_IDX_INIT_CFG_s tempInitCfg;
    void *pTempIdxBuf = NULL;
    AMP_FILE_STREAM_INIT_CFG_s fileInitCfg;
    void *pFileBuf = NULL;
    AMP_CFS_FILE_s *hg_UdtaFile;
    AMP_CFS_FILE_PARAM_s cfsParam = {0};
    void *EvtEncRawBuf;
    void *pStkRawBuf;
    UINT32 BufferSize = DummyVideoEnc_GetRequiredBufSize(EVTREC_ENC_RAW_SIZE, EVTREC_MAX_FIFO_NUM);

    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&g_pEncBuffer, &EvtEncRawBuf, BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    DummyVideoEnc_Init(&g_Encoder, BS_FN, HDR_FN, g_pEncBuffer, BufferSize, EVTREC_MAX_FIFO_NUM);

    AmpCFS_GetFileParam(&cfsParam);
    cfsParam.Mode = AMP_CFS_FILE_MODE_READ_ONLY;
    strcpy(cfsParam.Filename, UDTA_FN);
    hg_UdtaFile = AmpCFS_fopen(&cfsParam);
    if (hg_UdtaFile == NULL) {
        AmbaPrint("hIdxFile Open fail");
        goto ERR;
    } else {
        AmpCFS_fread(&g_Udta, 1, sizeof(g_Udta), hg_UdtaFile);
        AmpCFS_fclose(hg_UdtaFile);
    }

#if 0 /** for debug */
        AmbaPrint("g_Udta.nIdrInterval = %u", g_Udta.nIdrInterval);
        AmbaPrint("g_Udta.nTimeScale = %u", g_Udta.nTimeScale);
        AmbaPrint("g_Udta.nTickPerPicture = %u", g_Udta.nTickPerPicture);
        AmbaPrint("g_Udta.nN = %u", g_Udta.nN);
        AmbaPrint("g_Udta.nM = %u", g_Udta.nM);
        AmbaPrint("g_Udta.nVideoWidth = %u", g_Udta.nVideoWidth);
        AmbaPrint("g_Udta.nVideoHeight = %u", g_Udta.nVideoHeight);
#endif

    // create codec fifo
    AmpFifo_GetDefaultCfg(&fifoDefCfg);
    fifoDefCfg.hCodec = EVTREC_CODEC_HDLR;
    fifoDefCfg.IsVirtual = 0;
#ifndef USE_PREC_MUX
    fifoDefCfg.SyncRpOnWrite = 1;
#endif
    fifoDefCfg.NumEntries = EVTREC_MAX_FIFO_NUM;
    fifoDefCfg.cbEvent = DummyVideoEnc_EventCB;
    AmpFifo_Create(&fifoDefCfg, &g_pEncFifoHdlr);

#ifdef USE_PREC_MUX
    // create muxer fifo
    AmpFifo_GetDefaultCfg(&fifoDefCfg);
    fifoDefCfg.hCodec = EVTREC_CODEC_HDLR;
    fifoDefCfg.IsVirtual = 1;
    fifoDefCfg.NumEntries = EVTREC_MAX_FIFO_NUM;
    fifoDefCfg.cbEvent = AmpUT_EventRecord_FifoCB;
    AmpFifo_Create(&fifoDefCfg, &g_pMuxFifoHdlr);
#endif

    DummyVideoEnc_Reset(&g_Encoder, g_pEncFifoHdlr);

    // init format
    AmpFormat_GetInitDefaultCfg(&fmtInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&fmtInitCfg.Buffer, &pFmtBuf, fmtInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpFormat_Init(&fmtInitCfg);
    // init muxer
    AmpMuxer_GetInitDefaultCfg(&muxerInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&muxerInitCfg.Buffer, &pMuxerBuf, muxerInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpMuxer_Init(&muxerInitCfg);
#ifdef USE_PREC_MUX
    // init pre-record muxer
    PrecMux_GetInitDefaultCfg(&precInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&precInitCfg.Buffer, &pPrecBuf, precInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    PrecMux_Init(&precInitCfg);
#endif
    /** MP4 Mux Init */
    AmpMp4Mux_GetInitDefaultCfg(&MP4MuxInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&MP4MuxInitCfg.Buffer, &pMp4Buf, MP4MuxInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpMp4Mux_Init(&MP4MuxInitCfg) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Init Index Buffer Pool */
    AmpIndex_GetInitDefaultCfg(&IndexInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&IndexInitCfg.Buffer, &pIdxBuf, IndexInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpIndex_Init(&IndexInitCfg) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Init Temp Index */
    AmpTempIdx_GetInitDefaultCfg(&tempInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&tempInitCfg.Buffer, &pTempIdxBuf, tempInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpTempIdx_Init(&tempInitCfg) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    // init file stream
    AmpFileStream_GetInitDefaultCfg(&fileInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&fileInitCfg.Buffer, &pFileBuf, fileInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE)   != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpFileStream_Init(&fileInitCfg);

    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&g_pMuxStack, &pStkRawBuf, STACK_SIZE, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }

    /** Create Mux task */
    AmbaKAL_TaskCreate(&g_MuxTask, /** pTask */
    "UT_EvtRec_MuxTask", /** pTaskName */
    82, /** Priority */
    AmpUT_EventRecord_MuxTask, /** void (*EntryFunction)(UINT32) */
    0x0, /** EntryArg */
    g_pMuxStack,  /** pStackBase */
    STACK_SIZE, /** StackByteSize */
    AMBA_KAL_DO_NOT_START); /** AutoStart */

    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
ERR:
    AmbaPrint("[FAIL] %s", __FUNCTION__);
    return -1;
}

/**
 * Event record UT - start function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_EventRecord_start(void)
{
#ifdef USE_PREC_MUX
    // start from prec (parking mode)
    AMP_MUX_MOVIE_INFO_CFG_s movieCfg;
    AMP_FILE_STREAM_CFG_s fileCfg;
    AMP_TEMP_IDX_CFG_s tempCfg;
    PREC_MUX_CFG_s precCfg;
    AMP_MP4_MUX_CFG_s mp4Cfg;
    AMP_MUXER_PIPE_CFG_s muxPipeCfg;
    char szName[MAX_FILENAME_LENGTH] = {'\0'};
    char file[MAX_FILENAME_LENGTH] = {0};

    // open media info
    snprintf(file, MAX_FILENAME_LENGTH, "%s00.TMP", MP4_FN_PREFIX);
    strncpy(szName, file, MAX_FILENAME_LENGTH); // a dummy movie name
    szName[MAX_FILENAME_LENGTH - 1] = '\0';
    AmpFormat_NewMovieInfo(szName, &g_pMovie);
    // set media info
    AmpMuxer_GetDefaultMovieInfoCfg(&movieCfg);
    movieCfg.TrackCount = 1;
    movieCfg.Track[0].TrackType = AMP_MEDIA_TRACK_TYPE_VIDEO;
    movieCfg.Track[0].Fifo = g_pMuxFifoHdlr;
    movieCfg.Track[0].BufferBase = (UINT8 *)g_pEncBuffer;
    movieCfg.Track[0].BufferLimit = (UINT8 *)g_pEncBuffer + EVTREC_ENC_RAW_SIZE;
    movieCfg.Track[0].MediaId = AMP_FORMAT_MID_AVC;
    movieCfg.Track[0].TimeScale = g_Udta.nTimeScale;//atoi(Rate);
    movieCfg.Track[0].TimePerFrame = g_Udta.nTickPerPicture;//atoi(Scale);
    movieCfg.Track[0].Info.Video.Mode = AMP_VIDEO_MODE_P;
    movieCfg.Track[0].Info.Video.M = g_Udta.nM;//atoi(M);
    movieCfg.Track[0].Info.Video.N = g_Udta.nN;//atoi(N);
    movieCfg.Track[0].Info.Video.GOPSize = (UINT32)movieCfg.Track[0].Info.Video.N * g_Udta.nIdrInterval;//atoi(idrItvl);
    movieCfg.Track[0].Info.Video.CodecTimeScale = 90000;    // TODO: should remove CodecTimeScale, but the sample clip uses 90K
    movieCfg.Track[0].Info.Video.Width = g_Udta.nVideoWidth;//atoi(Width);
    movieCfg.Track[0].Info.Video.Height = g_Udta.nVideoHeight;//atoi(Height);
    AmpMuxer_InitMovieInfo(g_pMovie, &movieCfg);

    // create file stream
    AmpFileStream_GetDefaultCfg(&fileCfg);
    AmpFileStream_Create(&fileCfg, &g_pStream);
    // create Index
    AmpTempIdx_GetDefaultCfg(&tempCfg);
    if (AmpTempIdx_Create(&tempCfg, &g_pIndex) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    // create pre-record muxer
    PrecMux_GetDefaultCfg(&precCfg);
    precCfg.Length = EVENT_PREC_LENGTH;
    if (PrecMux_Create(&precCfg, &g_pPrecMux) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    // create Mp4Mux
    AmpMp4Mux_GetDefaultCfg(&mp4Cfg);
    mp4Cfg.Stream = g_pStream;
    mp4Cfg.Index = g_pIndex;
    if (AmpMp4Mux_Create(&mp4Cfg, &g_pMp4Mux) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    // create muxer pipe
    AmpMuxer_GetDefaultCfg(&muxPipeCfg);
    muxPipeCfg.FormatCount = 1;
    muxPipeCfg.Format[0] = g_pPrecMux;
    muxPipeCfg.Media[0] = (AMP_MEDIA_INFO_s *)g_pMovie;
    muxPipeCfg.OnEvent = AmpUT_EventRecord_MuxCB;
    if (AmpMuxer_Create(&muxPipeCfg, &g_pMuxPipe) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpMuxer_Add(g_pMuxPipe) != AMP_OK){
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpMuxer_Start(g_pMuxPipe, AMBA_KAL_NO_WAIT) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
#endif
    if (DummyVideoEnc_Start(&g_Encoder) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmbaKAL_TaskResume(&g_MuxTask);
    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
ERR:
    AmbaPrint("[FAIL] %s", __FUNCTION__);
    return -1;
}


/**
 * Event record UT - Event record test function.
 */
static int AmpUT_EventRecordTest(struct _AMBA_SHELL_ENV_s_ *env, int argc, char **argv)
{
//    AmbaPrint("%s cmd: %s", __FUNCTION__, argv[1]);
    if (strcmp(argv[1], "init") == 0) {
        AmpUT_EventRecord_init();
    } else if (strcmp(argv[1], "start") == 0) {
        AmpUT_EventRecord_start();
    } else if (strcmp(argv[1], "event") == 0) {
        AmpUT_EventRecord_event();
    }
    return 0;
}

/**
 * Event record UT - add Event record test function.
 */
int AmpUT_EventRecordTestAdd(void)
{
    // hook command
    AmbaTest_RegisterCommand("evtrec", AmpUT_EventRecordTest);

    return AMP_OK;
}

