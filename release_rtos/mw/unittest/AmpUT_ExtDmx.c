/**
 *  @file AmpUT_ExtDmx.c
 *
 *  **History**
 *      |Date       |Name        |Comments       |
 *      |-----------|------------|---------------|
 *      |2014/03/27 |clchan      |Created        |
 *
 *
 *  @copyright 2013 Ambarella Corporation. All rights reserved.
 *                 No part of this file may be reproduced, stored in a retrieval system,
 *                 or transmitted, in any form, or by any means, electronic, mechanical, photocopying,
 *                 recording, or otherwise, without the prior consent of Ambarella Corporation.
 */

#include <player/Decode.h>
#include <player/VideoDec.h>
#include "AmpUnitTest.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <AmbaCache_Def.h>
#include "DummyVideoDec.h"

#include <format/Demuxer.h>
#include <format/ExtDmx.h>
#include <util.h>
#include "ExtStream.h"

#define BS_FN   "C:\\OUT_0001.h264" /**< bitstream file name */
#define HDR_FN  "C:\\OUT_0001.nhnt" /**< nhnt file name */
#define EXT_FN  "C:\\TEST.EXT" /**< ext file name */

#define EXTDMX_DEC_RAW_SIZE (10<<20) /**< 10MB raw buffer */
#define INDEX_BUFFER_SIZE  (1<<20) /**< 1MB */
#define MAX_FIFO_ENTRY_NUM  1024 /**< number of the FIFO entry */

static AMP_STREAM_HDLR_s *g_pStream = NULL; /**< stream handler */
static AMP_DMX_FORMAT_HDLR_s *g_pFormat = NULL; /**< format handler */
static AMP_MOVIE_INFO_s *g_pMovie = NULL; /**< movie information */
static AMP_DEMUXER_PIPE_HDLR_s *g_pDmxPipe = NULL; /**< demuxer pipe */

#define EXTDMX_CODEC_HDLR ((void *)0x1234) /**< codec handler */

static void *g_ExtDmxBuf = NULL; /**< demuxer buffer */
static AMP_FIFO_HDLR_s *g_ExtDecFifoHdlr = NULL; /**< decode FIFO handler */
static AMP_FIFO_HDLR_s *g_ExtDmxFifoHdlr = NULL; /**< demux FIFO handler */
static DummyVideoDec_s g_Decoder; /**< video decoder */

/**
 * External dmx UT - data request function.
 *
 * @param [in] pDecoder decoder handler.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUt_ExtDmx_DataRequest(void *pDecoder)
{
    return AmpDemuxer_OnDataRequest(g_ExtDmxFifoHdlr);
}

/**
 * External dmx UT - decode FIFO callback function.
 *
 * @param [in] hdlr FIFO handler.
 * @param [in] event event id.
 * @param [in] Info callback information.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DecFifoCB(void *hdlr, UINT32 event, void* info)
{
    //AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    AMP_FIFO_INFO_s pTmpInfo;
    AMP_BITS_DESC_s *pTmpDesc = NULL;
    RING_BUFFER_INFO_s RingBufInfo = {0};
    if (event == AMP_FIFO_EVENT_GET_WRITE_POINT) {
        pTmpDesc = (AMP_BITS_DESC_s *) info;
        if (RingBuf_GetInfo(&g_Decoder.RingBuf, &RingBufInfo) != 0)
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        pTmpDesc->Size = RingBufInfo.nRingBufFreeSize;
        pTmpDesc->StartAddr = RingBufInfo.pRingBufWp;
        if (pTmpDesc->StartAddr == NULL)
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
    } else if (event == AMP_FIFO_EVENT_DATA_READY) {
        if (AmpFifo_GetInfo(g_ExtDecFifoHdlr, &pTmpInfo) != AMP_OK)
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        if (pTmpInfo.AvailEntries > 0) {
            if (AmpFifo_PeekEntry(g_ExtDecFifoHdlr, &pTmpDesc, (pTmpInfo.AvailEntries - 1)) != AMP_OK) {
                AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            } else {
                if (pTmpDesc->Size < AMP_FIFO_MARK_EOS) {
                    if (RingBuf_UpdateWp(&g_Decoder.RingBuf, pTmpDesc->StartAddr, pTmpDesc->Size) != 0)
                        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
                }
            }
        }
    }
    return 0;
}

/**
 * External dmx UT - demux FIFO callback function.
 *
 * @param [in] hdlr FIFO handler.
 * @param [in] event event id.
 * @param [in] Info callback information.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DmxFifoCB(void *hdlr, UINT32 event, void* info)
{
//    AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    return 0;
}

/**
 * External dmx UT - demux callback function.
 *
 * @param [in] hdlr demuxer handler.
 * @param [in] event event id.
 * @param [in] Info callback information.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DmxCB(void *hdlr, UINT32 event, void* info)
{
//    AmbaPrint("%s on Event: 0x%x", __FUNCTION__, event);

    switch (event) {
    case AMP_DEMUXER_EVENT_START:
        AmbaPrint("AMP_DEMUXER_EVENT_START");
        DummyVideoDec_Start(&g_Decoder);
        break;
    case AMP_DEMUXER_EVENT_END:
        AmbaPrint("AMP_DEMUXER_EVENT_END");
        DummyVideoDec_Stop(&g_Decoder);
        AmbaPrint("[SUCCESS] AmpUT_ExtDmx : End");
        break;
    default:
        AmbaPrint("[FAIL] %s: event = %u", __FUNCTION__, event);
        break;
    }
    return 0;
}

/**
 * External dmx UT - demux initiate function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DmxInit(void)
{
    AMP_FORMAT_INIT_CFG_s fmtInitCfg;
    void *pFmtBuf = NULL;
    AMP_DEMUXER_INIT_CFG_s demuxerInitCfg;
    void *pDemuxerBuf = NULL;
    AMP_EXT_DMX_INIT_CFG_s extInitCfg;
    void *pExtBuf = NULL;
    AMP_EXT_STREAM_INIT_CFG_s fileInitCfg;
    void *pFileBuf = NULL;
    void *ExtDmxRawBuf = NULL;
    const UINT32 BufferSize = DummyVideoDec_GetRequiredBufSize(EXTDMX_DEC_RAW_SIZE, MAX_FIFO_ENTRY_NUM);

    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&g_ExtDmxBuf, &ExtDmxRawBuf, BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    DummyVideoDec_Init(&g_Decoder, BS_FN, HDR_FN, g_ExtDmxBuf, BufferSize, MAX_FIFO_ENTRY_NUM, AmpUt_ExtDmx_DataRequest);
    /** Initial Format */
    AmpFormat_GetInitDefaultCfg(&fmtInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&fmtInitCfg.Buffer, &pFmtBuf, fmtInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpFormat_Init(&fmtInitCfg);
    /** Initial Demuxer */
    AmpDemuxer_GetInitDefaultCfg(&demuxerInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&demuxerInitCfg.Buffer, &pDemuxerBuf, demuxerInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpDemuxer_Init(&demuxerInitCfg);
    /** Initial External Demux */
    AmpExtDmx_GetInitDefaultCfg(&extInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&extInitCfg.Buffer, &pExtBuf, extInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpExtDmx_Init(&extInitCfg);
    /** Initial File system */
    AmpExtStream_GetInitDefaultCfg(&fileInitCfg);
    if (AmpUtil_GetAlignedPool(&G_MMPL, (void **)&fileInitCfg.Buffer, &pFileBuf, fileInitCfg.BufferSize, AMBA_CACHE_LINE_SIZE) != OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    AmpExtStream_Init(&fileInitCfg);

    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
ERR:
    AmbaPrint("[FAIL] %s", __FUNCTION__);
    return -1;
}

/**
 * External dmx UT - demux open function.
 *
 * @param [in] szName file name.
 * @param [in] Speed demux speed.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DmxOpen(char *szName, UINT32 Speed)
{
    AMP_FIFO_CFG_s fifoDefCfg = {0};
    AMP_EXT_STREAM_CFG_s fileCfg;
    AMP_DEMUXER_PIPE_CFG_s dmxCfg;
    AMP_EXT_DMX_CFG_s extCfg = {0};
    AMP_DMX_MOVIE_INFO_CFG_s MovieCfg;

    /** Create decoder fifo */
    AmpFifo_GetDefaultCfg(&fifoDefCfg);
    fifoDefCfg.hCodec = EXTDMX_CODEC_HDLR;
    fifoDefCfg.IsVirtual = 0;
    fifoDefCfg.NumEntries = MAX_FIFO_ENTRY_NUM;
    fifoDefCfg.cbEvent = AmpUT_ExtDmx_DecFifoCB;
    if (AmpFifo_Create(&fifoDefCfg, &g_ExtDecFifoHdlr) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Create demux fifo */
    AmpFifo_GetDefaultCfg(&fifoDefCfg);
    fifoDefCfg.hCodec = EXTDMX_CODEC_HDLR;
    fifoDefCfg.IsVirtual = 1;
    fifoDefCfg.NumEntries = MAX_FIFO_ENTRY_NUM;
    fifoDefCfg.cbEvent = AmpUT_ExtDmx_DmxFifoCB;
    if (AmpFifo_Create(&fifoDefCfg, &g_ExtDmxFifoHdlr) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Open File system */
    AmpExtStream_GetDefaultCfg(&fileCfg);
    AmpExtStream_Create(&fileCfg, &g_pStream);
    if (g_pStream->Func->Open(g_pStream, szName, AMP_STREAM_MODE_RDONLY) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Open Media info (extdmx) */
    if (AmpFormat_GetMovieInfo(szName, AmpExtDmx_Parse, g_pStream, &g_pMovie) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Inifial Demuxer */
    AmpDemuxer_GetDefaultMovieInfoCfg(&MovieCfg, g_pMovie);
    MovieCfg.Track[0].Fifo = g_ExtDmxFifoHdlr;
    MovieCfg.Track[0].BufferBase = g_ExtDmxBuf;
    MovieCfg.Track[0].BufferLimit = (UINT8 *)g_ExtDmxBuf + EXTDMX_DEC_RAW_SIZE;
    AmpDemuxer_InitMovieInfo(g_pMovie, &MovieCfg);
    // open extdmx
    AmpExtDmx_GetDefaultCfg(AMP_MEDIA_INFO_MOVIE, &extCfg);
    extCfg.Stream = g_pStream;
    if (AmpExtDmx_Create(&extCfg, &g_pFormat) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    /** Create Demuxer pipe */
    AmpDemuxer_GetDefaultCfg(&dmxCfg);
    dmxCfg.FormatCount = 1;
    dmxCfg.Format[0] = g_pFormat;
    dmxCfg.Media[0] = (AMP_MEDIA_INFO_s *)g_pMovie;
    dmxCfg.OnEvent = AmpUT_ExtDmx_DmxCB;
    dmxCfg.Speed = Speed;
    if (AmpDemuxer_Create(&dmxCfg, &g_pDmxPipe) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    if (AmpDemuxer_Add(g_pDmxPipe) != AMP_OK) {
        AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
        goto ERR;
    }
    DummyVideoDec_Reset(&g_Decoder, g_ExtDecFifoHdlr);
    return 0;
ERR:
    AmbaPrint("[FAIL] %s", __FUNCTION__);
    return -1;
}

/**
 * External dmx UT - demux close function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_DmxClose(void)
{
    if (g_pDmxPipe != NULL) {
        if (AmpDemuxer_WaitComplete(g_pDmxPipe, AMBA_KAL_WAIT_FOREVER) != AMP_OK) {
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            return -1;
        }
        if (AmpDemuxer_Remove(g_pDmxPipe) != AMP_OK) {
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            return -1;
        }
        if (AmpDemuxer_Delete(g_pDmxPipe) != AMP_OK) {
            AmbaPrint("%s:%u", __FUNCTION__, __LINE__);
            return -1;
        }
        g_pDmxPipe = NULL;
    }

    if (g_pFormat != NULL) {
        AmpExtDmx_Delete(g_pFormat);
        g_pFormat = NULL;
    }

    if (g_pStream != NULL) {
        g_pStream->Func->Close(g_pStream);
        AmpExtStream_Delete(g_pStream);
        g_pStream = NULL;
    }

    if (g_pMovie != NULL) {
        AmpFormat_RelMovieInfo(g_pMovie, FALSE);
        g_pMovie = NULL;
    }

    if (g_ExtDmxFifoHdlr != NULL) {
        AmpFifo_Delete(g_ExtDmxFifoHdlr);
        g_ExtDmxFifoHdlr = NULL;
    }

    if (g_ExtDecFifoHdlr != NULL) {
        AmpFifo_Delete(g_ExtDecFifoHdlr);
        g_ExtDecFifoHdlr = NULL;
    }

    return 0;
}

/**
 * External dmx UT - initiate function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_init(void)
{
    /** Initial Ext demux */
    if (AmpUT_ExtDmx_DmxInit() != 0)
        AmbaPrint("[FAIL] %s", __FUNCTION__);
    return 0;
}

/**
 * External dmx UT - start function.
 *
 * @param [in] StartTime start demux time.
 * @param [in] Direction demux direction.
 * @param [in] Speed demux speed.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_start(UINT32 StartTime, UINT8 Direction, UINT32 Speed)
{
    /** Open Ext demux */
    int rval;
    UINT32 speed = ((Speed == 0) ? 1 : Speed);
    rval = AmpUT_ExtDmx_DmxOpen(EXT_FN, speed); if (rval != AMP_OK) { goto ERR; }

    if (Direction == 0) {
        AmbaPrint("Ext Demux - Forward");
        rval = AmpDemuxer_SetProcParam(g_pDmxPipe, 1200); if (rval != AMP_OK) { goto ERR; }
        if ((StartTime == 0) && (speed == 1))
            rval = AmpDemuxer_Start(g_pDmxPipe);
        else
            rval = AmpDemuxer_Seek(g_pDmxPipe, StartTime, Direction, speed);
        if (rval != AMP_OK) { goto ERR; }
        AmpDemuxer_OnDataRequest(g_ExtDmxFifoHdlr);
        AmbaKAL_TaskSleep(100);
        rval = AmpDemuxer_SetProcParam(g_pDmxPipe, 200); if (rval != AMP_OK) { goto ERR; }
    } else if (Direction == 1) {
        AmbaPrint("Ext Demux - Backward");
        rval = AmpDemuxer_SetProcParam(g_pDmxPipe, 1200); if (rval != AMP_OK) { goto ERR; }
        rval = AmpDemuxer_Seek(g_pDmxPipe, StartTime, Direction, speed); if (rval != AMP_OK) { goto ERR; }
        AmpDemuxer_OnDataRequest(g_ExtDmxFifoHdlr);
        AmbaKAL_TaskSleep(100);
        rval = AmpDemuxer_SetProcParam(g_pDmxPipe, 200); if (rval != AMP_OK) { goto ERR; }
    } else {
        AmbaPrint("%s, Error Direction", __FUNCTION__);
    }
    return 0;
ERR:
    AmbaPrint("[FAIL] %s", __FUNCTION__);
    return -1;
}

/**
 * External dmx UT - stop function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_stop(void)
{
    AmbaPrint("%s", __FUNCTION__);
    AmpDemuxer_Stop(g_pDmxPipe);
    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
}

/**
 * External dmx UT - exit function.
 */
static int AmpUT_ExtDmx_exit(void)
{
    AmbaPrint("%s", __FUNCTION__);
    AmpUT_ExtDmx_DmxClose();
    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
}

/**
 * External dmx UT - usage describe function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_Usage(void)
{
    AmbaPrint("Ext Demux Test Command");
    AmbaPrint("----------------------");
    AmbaPrint("1. init - start demux");
    AmbaPrint("2. start - start demux");
    AmbaPrint("3. stop - stop demux");
    AmbaPrint("4. exit - exit demux");
    return 0;
}

/**
 * External dmx UT - start usage describe function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_StartUsage(void)
{
    AmbaPrint("Ext Demux Test Command - start");
    AmbaPrint("------------------------------");
    AmbaPrint("start $time $direction $speed");
    AmbaPrint("");
    AmbaPrint("$time      - From what time(million second) of clip to demux.");
    AmbaPrint("$direction - 0 : Forward, 1 : Backward.");
    AmbaPrint("$speed     - 1, 2, 4, 8 fold to demux, only effected in forward demux.");
    AmbaPrint("------------------------------");
    AmbaPrint("Ex. start 0 0 0");
    AmbaPrint("Ex. start 5000 1 0");
    return 0;
}

/**
 * External dmx UT - feed function.
 *
 * @param [in] Time time for feed.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_feed(UINT32 Time)
{
    AmpUT_ExtDmx_DmxOpen(EXT_FN, 1);
    AmpDemuxer_FeedFrame(g_pFormat, 0, Time, AMP_FIFO_TYPE_IDR_FRAME);
    AmpUT_ExtDmx_DmxClose();
    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
}

/**
 * External dmx UT - seek function.
 *
 * @param [in] nTime time to seek.
 * @param [in] nDirection demux direction.
 * @param [in] nSpeed demux speed.
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_seek(UINT32 nTime, UINT8 nDirection, UINT32 nSpeed)
{
    AmpDemuxer_Seek(g_pDmxPipe, nTime, nDirection, ((nSpeed == 0) ? 1 : nSpeed));
    AmbaPrint("[SUCCESS] %s", __FUNCTION__);
    return 0;
}

/**
 * External dmx UT - test function.
 *
 * @return 0 - OK, others - fail
 *
 */
static int AmpUT_ExtDmx_test(void)
{
    return 0;
}

/**
 * External dmx UT - External dmx test function.
 */
static int AmpUT_ExtDmxTest(struct _AMBA_SHELL_ENV_s_ *env, int argc, char **argv)
{
    int rval = 0;

//    AmbaPrint("%s cmd: %s", __FUNCTION__, argv[1]);
    if (strcmp(argv[1], "init") == 0) {
        AmpUT_ExtDmx_init();
    } else if (strcmp(argv[1], "start") == 0) {
        if (argc == 5) {
            UINT32 StartTime;
            UINT8 Direction;
            UINT32 Speed;

            StartTime = atoi(argv[2]);
            Direction = atoi(argv[3]);
            Speed = atoi(argv[4]);
            AmbaPrint("extdmx start %u %u %u", StartTime, Direction, Speed);
            AmpUT_ExtDmx_start(StartTime, Direction, Speed);
        } else if (argc == 2) {
            AmbaPrint("extdmx start");
            AmpUT_ExtDmx_start(0, 0, 1);
        } else {
            AmbaPrint("\t Wrong Parameters!");
            AmbaPrint("");
            AmpUT_ExtDmx_StartUsage();
            rval = -1;
        }
    } else if (strcmp(argv[1], "feed") == 0) {
        if (argc == 3) {
            UINT32 Time;

            Time = atoi(argv[2]);
            AmpUT_ExtDmx_feed(Time);
        } else {
            AmbaPrint("\t Wrong Parameters!");
            AmbaPrint("");
            rval = -1;
        }
    } else if (strcmp(argv[1], "stop") == 0) {
        AmpUT_ExtDmx_stop();
    } else if (strcmp(argv[1], "exit") == 0) {
        AmpUT_ExtDmx_exit();
    } else if (strcmp(argv[1], "seek") == 0) {
        if (argc == 5) {
            UINT8 Direction;
            UINT32 Time;
            UINT32 Speed;

            Time = atoi(argv[2]);
            Direction = atoi(argv[3]);
            Speed = atoi(argv[4]);
            AmpUT_ExtDmx_seek(Time, Direction, Speed);
        } else {
            AmbaPrint("\t Wrong Parameters!");
            AmbaPrint("");
            rval = -1;
        }
    } else if (strcmp(argv[1], "test") == 0) {
        AmpUT_ExtDmx_test();
    } else {
        AmpUT_ExtDmx_Usage();
    }

    return rval;
}

/**
 * External dmx UT - add External dmx test function.
 */
int AmpUT_ExtDmxTestAdd(void)
{
    AmbaTest_RegisterCommand("extdmx", AmpUT_ExtDmxTest);/**< hook command */
    return AMP_OK;
}

