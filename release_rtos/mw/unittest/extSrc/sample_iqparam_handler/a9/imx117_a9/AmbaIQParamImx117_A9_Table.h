/*-------------------------------------------------------------------------------------------------------------------*\
 *  @FileName       :: AmbaIQParamImx117_A9_Table.h
 *
 *  @Copyright      :: Copyright (C) 2012 Ambarella Corporation. All rights reserved.
 *
 *                     No part of this file may be reproduced, stored in a retrieval system,
 *                     or transmitted, in any form, or by any means, electronic, mechanical, photocopying,
 *                     recording, or otherwise, without the prior consent of Ambarella Corporation.
 *
 *  @Description    :: Imx144 Image IQ parameters tables
 *
 *  @History        ::
 *      Date        Name        Comments
 *      01/08/2013  Eddie Chen  Created
\*-------------------------------------------------------------------------------------------------------------------*/
#ifdef CONFIG_SOC_A9
#ifndef __AMBA_IQPARAM_IMX117_A9_TABLE_H__
#define __AMBA_IQPARAM_IMX117_A9_TABLE_H__

#include "AmbaImg_Adjustment_A9.h"
#include "AmbaImg_AaaDef.h"
#include "AmbaImg_Adjustment_Def.h"

extern IMG_PARAM_s AmbaIQParamImx117ImageParam;
extern AAA_PARAM_s AmbaIQParamImx117DefParams;
extern ADJ_TABLE_PARAM_s AmbaIQParamImx117AdjTableParam;
extern ADJ_VIDEO_PARAM_s AmbaIQParamImx117AdjVideoPc00;
extern ADJ_VIDEO_PARAM_s AmbaIQParamImx117AdjVideoPc01;0;
extern ADJ_STILL_FAST_LISO_PARAM_S AmbaIQParamImx117AdjStillLIso00;
extern ADJ_STILL_FAST_LISO_PARAM_S AmbaIQParamImx117AdjStillLIso01;
extern ADJ_PHOTO_PARAM_s AmbaIQParamImx117AdjPhotoPreview00;
extern ADJ_PHOTO_PARAM_s AmbaIQParamImx117AdjPhotoPreview01;
extern ADJ_STILL_HISO_PARAM_s AmbaIQParamImx117AdjStillHIso00;
extern ADJ_STILL_HISO_PARAM_s AmbaIQParamImx117AdjStillHIso01;
extern ADJ_STILL_IDX_INFO_s AmbaIQParamImx117StillParam;
extern SCENE_DATA_s SceneDataS01Imx117A9[8];
extern SCENE_DATA_s SceneDataS02Imx117A9[8];
extern SCENE_DATA_s SceneDataS03Imx117A9[8];
extern SCENE_DATA_s SceneDataS04Imx117A9[8];
extern SCENE_DATA_s SceneDataS05Imx117A9[8];
extern DE_PARAM_s DeVideoParamImx117A9;
extern DE_PARAM_s DeStillParamImx117A9;
//extern CALIBRATION_PARAM_s AmbaIQParamImx117CalibParams;

COLOR_TABLE_PATH_s GCcTableIMX117[10] = {
    { 0,
      "VideoCc0_Imx117",
      "VideoCc1_Imx117",
      "VideoCc2_Imx117",
      "VideoCc3_Imx117",
      "VideoCc4_Imx117",
      "StillCc0_Imx117",
      "StillCc1_Imx117",
      "StillCc2_Imx117",
      "StillCc3_Imx117",
      "StillCc4_Imx117",
    },
    { 1,
      "cc3d_cc_bw_gamma_lin_video_Imx117",
      "cc3d_cc_bw_gamma_lin_video_Imx117",
      "cc3d_cc_bw_gamma_lin_video_Imx117",
      "cc3d_cc_bw_gamma_lin_video_Imx117",
      "cc3d_cc_bw_gamma_lin_video_Imx117",
      "cc3d_cc_bw_gamma_lin_still_Imx117",
      "cc3d_cc_bw_gamma_lin_still_Imx117",
      "cc3d_cc_bw_gamma_lin_still_Imx117",
      "cc3d_cc_bw_gamma_lin_still_Imx117",
      "cc3d_cc_bw_gamma_lin_still_Imx117",
    },
    { -1 },
};

IP_TABLE_PATH_s GVideoAdjTablePathIMX117[ADJ_VIDEO_TABLE_VALID_NO] = {
    "adj_video_default_00_Imx117",
    "adj_video_default_01_Imx117",
};

IP_TABLE_PATH_s GPhotoAdjTablePathIMX117[ADJ_PHOTO_TABLE_VALID_NO] = {
    "adj_photo_default_00_Imx117",
    "adj_photo_default_01_Imx117",
};

IP_TABLE_PATH_s GStillLIsoAdjTablePathIMX117[ADJ_STILL_LISO_TABLE_VALID_NO] = {
    "adj_still_default_00_Imx117",
    "adj_still_default_01_Imx117",
};

IP_TABLE_PATH_s GStillHIsoAdjTablePathIMX117[ADJ_STILL_HISO_TABLE_VALID_NO] = {
    "adj_hiso_still_default_00_Imx117",
//    "adj_hiso_still_default_01_Imx117",
};

IP_TABLE_PATH_s GSceneDataTablePathIMX117[SCENE_TABLE_VALID_NO] = {
    "scene_data_s01_Imx117",
    "scene_data_s02_Imx117",
    "scene_data_s03_Imx117",
    "scene_data_s04_Imx117",
    "scene_data_s05_Imx117",
};

IP_TABLE_PATH_s GImgAdjTablePathIMX117 ={
    "img_default_Imx117"
};    

IP_TABLE_PATH_s GAaaAdjTablePathIMX117 ={
    "aaa_default_Imx117"
};    

IP_TABLE_PATH_s GStillIdxInfoAdjTablePathIMX117 ={
    "adj_still_idx_Imx117"
};    
    
IP_TABLE_PATH_s GDeVideoTablePathIMX117 ={
    "de_default_video_Imx117"
};   

IP_TABLE_PATH_s GDeStillTablePathIMX117 ={
    "de_default_still_Imx117"
};    
IP_TABLE_PATH_s GAdjTablePathIMX117 ={
    "adj_table_param_default_Imx117"
};   

#endif
#endif