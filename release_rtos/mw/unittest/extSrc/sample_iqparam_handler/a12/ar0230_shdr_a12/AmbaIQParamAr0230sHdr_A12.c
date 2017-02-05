/*-------------------------------------------------------------------------------------------------------------------*\
 *  @FileName       :: AmbaIQParamAr0230sHdr_A12.c
 *
 *  @Copyright      :: Copyright (C) 2013 Ambarella Corporation. All rights reserved.
 *
 *                     No part of this file may be reproduced, stored in a retrieval system,
 *                     or transmitted, in any form, or by any means, electronic, mechanical, photocopying,
 *                     recording, or otherwise, without the prior consent of Ambarella Corporation.
 *
 *  @Description    :: Implementation of SONY AR0230shdr related settings.
 *
 *  @History        ::
 *      Date        Name        Comments
 *      07/16/2013  Eathan Wu Created
 *
\*-------------------------------------------------------------------------------------------------------------------*/
#ifdef CONFIG_SOC_A12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "AmbaDataType.h"
#include "AmbaPrint.h"
#include "AmbaFS.h"
#include "AmbaUtility.h"

#include "AmbaImg_Adjustment_A12.h"
#include "AmbaIQParamHandler.h"
#include "AmbaIQParamAr0230sHdr_A12_Table.h"

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Init
 *
 *  @Description:: Init function for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    int : 0(OK)/-1(NG)
\*-----------------------------------------------------------------------------------------------*/
static int AmbaIQParamAr0230sHdr_A12_Init(void)
{
    return 0;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Color_Table_Path
 *
 *  @Description:: Get color table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    COLOR_TABLE_PATH_s * : Return color table path address.
\*-----------------------------------------------------------------------------------------------*/
static COLOR_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Color_Table_Path(void)
{
    return GCcTableAR0230shdr;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Table_Path
 *
 *  @Description:: Get adj video table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Table_Path(int paramLoaded, int tableNo)
{
    return &GVideoAdjTablePathAR0230shdr[tableNo];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_High_Iso_Table_Path
 *
 *  @Description:: Get adj video high iso table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_High_Iso_Table_Path(int paramLoaded, int tableNo)
{
    return &GVideoHIsoAdjTablePathAR0230shdr[tableNo];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Photo_Table_Path
 *
 *  @Description:: Get adj photo table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Photo_Table_Path(int paramLoaded, int tableNo)
{
    return &GPhotoAdjTablePathAR0230shdr[tableNo];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Low_Iso_Table_Path
 *
 *  @Description:: Get adj still low iso table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Low_Iso_Table_Path(int paramLoaded, int tableNo)
{
    return &GStillLIsoAdjTablePathAR0230shdr[tableNo];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_High_Iso_Table_Path
 *
 *  @Description:: Get adj still high iso table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_High_Iso_Table_Path(int paramLoaded, int tableNo)
{
    return &GStillHIsoAdjTablePathAR0230shdr[tableNo];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Scene_Data_Table_Path
 *
 *  @Description:: Get scene mode data table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return IQ table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Scene_Data_Table_Path(int paramLoaded, int sceneSet)
{
    return &GSceneDataTablePathAR0230shdr[sceneSet];
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Param_Table_Path
 *
 *  @Description:: Get param table path for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    PARAM_TABLE_PATH_s * : Return param table path address.
\*-----------------------------------------------------------------------------------------------*/
static PARAM_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Param_Table_Path(void)
{
    return NULL;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Img_Table_Path
 *
 *  @Description:: Get Image default img path for AR0230shdr sensor
 *
 *  @Input      ::
 *   
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s* : Return img table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Img_Table_Path(void)
{
    return &GImgAdjTablePathAR0230shdr;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Aaa_Table_Path
 *
 *  @Description:: Get Aaa default param table path for AR0230shdr sensor
 *
 *  @Input      ::
 *   
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return Aaa table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Aaa_Table_Path( int tableNo)
{
    return &GAaaAdjTablePathAR0230shdr[tableNo];
}
/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_AdjTable_Table_Path
 *
 *  @Description:: Get Adj Table path for AR0230shdr sensor
 *
 *  @Input      ::
 *   
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return AdjTable table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_AdjTable_Table_Path(void)
{
    return &GAdjTablePathAR0230shdr;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Idx_Info_Table_Path
 *
 *  @Description:: Get Still Idx Adj param table path for AR0230shdr sensor
 *
 *  @Input      ::
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return adj still idx info table table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Idx_Info_Table_Path(void)
{
    return &GStillIdxInfoAdjTablePathAR0230shdr;
}
/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Idx_Info_Table_Path
 *
 *  @Description:: Get Video Idx Adj param table path for AR0230shdr sensor
 *
 *  @Input      ::
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return video idx info table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Idx_Info_Table_Path(void)
{
    return &GVideoIdxInfoAdjTablePathAR0230shdr;
}

/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Get_De_Table_Path
 *
 *  @Description:: Get De param table pathfor AR0230shdr sensor
 *
 *  @Input      ::
 *    int mode      : 0: Video mode, 1: still mode
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    IP_TABLE_PATH_s * : Return De table path address.
\*-----------------------------------------------------------------------------------------------*/
static IP_TABLE_PATH_s* AmbaIQParamAr0230sHdr_A12_Get_De_Table_Path(int mode)
{
    switch(mode){
        case DE_PARAM_VIDEO:
        return &GDeVideoTablePathAR0230shdr;
            break;
    case DE_PARAM_STILL:
            return &GDeStillTablePathAR0230shdr;
        break;
    default:
        return &GDeVideoTablePathAR0230shdr;
        break;

    }

}



/*-----------------------------------------------------------------------------------------------*\
 *  @RoutineName:: AmbaIQParamAr0230sHdr_A12_Register
 *
 *  @Description:: Register parameter proxy for AR0230shdr sensor
 *
 *  @Input      ::
 *    None
 *
 *  @Output     ::
 *    None
 *
 *
 *  @Return     ::
 *    int : 0(OK)/-1(NG)
\*-----------------------------------------------------------------------------------------------*/
int AmbaIQParamAr0230sHdr_A12_Register(UINT32 chNo)
{
    PARAM_PROXY_s Par = {0};
    char DevName[] = {'a','r','0','2','3','0','s','h','d','r','_','a','1','2','\0'};

    Par.Id = 0;
    strcpy(Par.Name, DevName);

    Par.Init = AmbaIQParamAr0230sHdr_A12_Init;
    Par.GetColorTablePath = AmbaIQParamAr0230sHdr_A12_Get_Color_Table_Path;
    Par.GetParamTablePath = AmbaIQParamAr0230sHdr_A12_Get_Param_Table_Path;
    Par.GetAdjVideoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Table_Path;
    Par.GetAdjVideoHIsoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_High_Iso_Table_Path;    
    Par.GetAdjPhotoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Photo_Table_Path;
    Par.GetAdjStillLIsoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Low_Iso_Table_Path;
    Par.GetAdjStillHIsoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_High_Iso_Table_Path;
    Par.GetSceneDataTablePath = AmbaIQParamAr0230sHdr_A12_Get_Scene_Data_Table_Path;
    Par.GetImgTablePath = AmbaIQParamAr0230sHdr_A12_Get_Img_Table_Path;
    Par.GetAaaTablePath = AmbaIQParamAr0230sHdr_A12_Get_Aaa_Table_Path;   
    Par.GetAdjStillIdxInfoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Still_Idx_Info_Table_Path;
    Par.GetAdjVideoIdxInfoTablePath = AmbaIQParamAr0230sHdr_A12_Get_Adj_Video_Idx_Info_Table_Path;
    Par.GetDeTablePath = AmbaIQParamAr0230sHdr_A12_Get_De_Table_Path;
    Par.GetAdjTablePath = AmbaIQParamAr0230sHdr_A12_Get_AdjTable_Table_Path;
    
    AmbaIQParam_Attach(chNo, &Par);
    //AmbaPrint("%s, %s",__FUNCTION__, Par.Name);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
