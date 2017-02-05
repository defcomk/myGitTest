/**
  * @file src/app/apps/flow/widget/menu/connectedcam/menu_photo.h
  *
  * Header of Photo-related Menu Items
  *
  * History:
  *    2013/11/22 - [Martin Lai] created file
  *
  * Copyright (C) 2013, Ambarella, Inc.
  *
  * All rights reserved. No Part of this file may be reproduced, stored
  * in a retrieval system, or transmitted, in any form, or by any means,
  * electronic, mechanical, photocopying, recording, or otherwise,
  * without the prior consent of Ambarella, Inc.
  */
#ifndef APP_WIDGET_MENU_PHOTO_H_
#define APP_WIDGET_MENU_PHOTO_H_

__BEGIN_C_PROTO__

/*************************************************************************
 * photo menu definitions
 ************************************************************************/
typedef enum _MENU_PHOTO_ITEM_ID_e_ {
    MENU_PHOTO_MULTI_CAP = 0,
    MENU_PHOTO_CAP_MODE,
    MENU_PHOTO_SIZE,
    MENU_PHOTO_QUALITY,
    MENU_PHOTO_SELFTIMER,
    MENU_PHOTO_TIME_LAPSE,
    MENU_PHOTO_QUICKVIEW_DELAY,
    MENU_PHOTO_DIGITAL_ZOOM,
    MENU_PHOTO_STAMP,
    MENU_PHOTO_ITEM_NUM
} MENU_PHOTO_ITEM_ID_e;

typedef enum _MENU_PHOTO_MULTI_CAP_MODE_SEL_ID_e_ {
    MENU_PHOTO_MULTI_CAP_OFF = 0,
    MENU_PHOTO_MULTI_CAP_AEB,
    MENU_PHOTO_MULTI_CAP_SEL_NUM
} MENU_PHOTO_MULTI_CAP_MODE_SEL_ID_e;

typedef enum _MENU_PHOTO_NORM_CAP_MODE_SEL_ID_e_ {
    MENU_PHOTO_CAP_MODE_PRECISE = 0,
    MENU_PHOTO_CAP_MODE_PES,
    MENU_PHOTO_CAP_MODE_BURST,
    MENU_PHOTO_CAP_MODE_PRE_CAPTURE,
    MENU_PHOTO_CAP_MODE_SEL_NUM
} MENU_PHOTO_NORM_CAP_MODE_SEL_ID_e;

typedef enum _MENU_PHOTO_SIZE_SEL_ID_e_ {
    MENU_PHOTO_SIZE_1 = 0,
    MENU_PHOTO_SIZE_2,
    MENU_PHOTO_SIZE_3,
    MENU_PHOTO_SIZE_4,
    MENU_PHOTO_SIZE_5,
    MENU_PHOTO_SIZE_6,
    MENU_PHOTO_SIZE_7,
    MENU_PHOTO_SIZE_8,
    MENU_PHOTO_SIZE_9,
    MENU_PHOTO_SIZE_10,
    MENU_PHOTO_SIZE_SEL_NUM
} MENU_PHOTO_SIZE_SEL_ID_e;

typedef enum _MENU_PHOTO_QUALITY_SEL_ID_e_ {
    MENU_PHOTO_QUALITY_SFINE = 0,
    MENU_PHOTO_QUALITY_FINE,
    MENU_PHOTO_QUALITY_NORMAL,
    MENU_PHOTO_QUALITY_AUTO,
    MENU_PHOTO_QUALITY_SEL_NUM
} MENU_PHOTO_QUALITY_SEL_ID_e;

typedef enum _MENU_PHOTO_SELFTIMER_SEL_ID_e_ {
    MENU_PHOTO_SELFTIMER_OFF = 0,
    MENU_PHOTO_SELFTIMER_3S,
    MENU_PHOTO_SELFTIMER_5S,
    MENU_PHOTO_SELFTIMER_10S,
    MENU_PHOTO_SELFTIMER_SEL_NUM
} MENU_PHOTO_SELFTIMER_SEL_ID_e;

typedef enum _MENU_PHOTO_TIME_LAPSE_SEL_ID_e_ {
    MENU_PHOTO_TIME_LAPSE_OFF = 0,
    MENU_PHOTO_TIME_LAPSE_500MS,
    MENU_PHOTO_TIME_LAPSE_1S,
    MENU_PHOTO_TIME_LAPSE_5S,
    MENU_PHOTO_TIME_LAPSE_SEL_NUM
} MENU_PHOTO_TIME_LAPSE_SEL_ID_e;

typedef enum _MENU_PHOTO_QUICKVIEW_DELAY_SEL_ID_e_ {
    MENU_PHOTO_QUICKVIEW_DELAY_OFF = 0,
    MENU_PHOTO_QUICKVIEW_DELAY_1S,
    MENU_PHOTO_QUICKVIEW_DELAY_2S,
    MENU_PHOTO_QUICKVIEW_DELAY_3S,
    MENU_PHOTO_QUICKVIEW_DELAY_4S,
    MENU_PHOTO_QUICKVIEW_DELAY_5S,
    MENU_PHOTO_QUICKVIEW_DELAY_CONT,
    MENU_PHOTO_QUICKVIEW_DELAY_SEL_NUM
} MENU_PHOTO_QUICKVIEW_DELAY_SEL_ID_e;

typedef enum _MENU_PHOTO_DIGITAL_ZOOM_SEL_ID_e_ {
    MENU_PHOTO_DIGITAL_ZOOM_OFF = 0,
    MENU_PHOTO_DIGITAL_ZOOM_ON,
    MENU_PHOTO_DIGITAL_ZOOM_NUMX,
    MENU_PHOTO_DIGITAL_ZOOM_SEL_NUM
} MENU_PHOTO_DIGITAL_ZOOM_SEL_ID_e;

typedef enum _MENU_PHOTO_STAMP_SEL_ID_e_ {
    MENU_PHOTO_STAMP_OFF = 0,
    MENU_PHOTO_STAMP_DATE,
    MENU_PHOTO_STAMP_TIME,
    MENU_PHOTO_STAMP_BOTH,
    MENU_PHOTO_STAMP_SEL_NUM
} MENU_PHOTO_STAMP_SEL_ID_e;

__END_C_PROTO__

#endif /* APP_WIDGET_MENU_PHOTO_H_ */
