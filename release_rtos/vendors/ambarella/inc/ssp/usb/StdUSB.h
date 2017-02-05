/*-------------------------------------------------------------------------------------------------------------------*\
 *  @FileName       :: StdUSB.h
 *
 *  @Copyright      :: Copyright (C) 2014 Ambarella Corporation. All rights reserved.
 *
 *                     No part of this file may be reproduced, stored in a retrieval system,
 *                     or transmitted, in any form, or by any means, electronic, mechanical, photocopying,
 *                     recording, or otherwise, without the prior consent of Ambarella Corporation.
 *
 *  @Description    :: Standard USB header file.
 *
 *  @History        ::
 *      Date        Name        Comments
 *      10/09/2014  pwchen      Created
 *
\*-------------------------------------------------------------------------------------------------------------------*/

#ifndef _STD_USB_H_
#define _STD_USB_H_

#define DESC_EP_ATTR_CONTROL            0
#define DESC_EP_ATTR_ISO                0x01
#define DESC_EP_ATTR_BULK               0x02
#define DESC_EP_ATTR_INT                0x03
#define DESC_EP_DIR_OUT                 0x00
#define DESC_EP_DIR_IN                  0x80

#define USB_DESC_LENGTH_DEV          0x12
#define USB_DESC_LENGTH_CFG          0x09
#define USB_DESC_LENGTH_INTF         0x09
#define USB_DESC_LENGTH_QUALIFIER    0x0A
#define USB_DESC_LENGTH_ENDPOINT     0x07
#define USB_DESC_LENGTH_IAD          0x08

#define USB_DESC_TYPE_DEV           0x01
#define USB_DESC_TYPE_CFG           0x02
#define USB_DESC_TYPE_STRING        0x03
#define USB_DESC_TYPE_INTF          0x04
#define USB_DESC_TYPE_ENDPOINT      0x05
#define USB_DESC_TYPE_QUALIFIER     0x06
#define USB_DESC_TYPE_IAD           0x0B
#define USB_DESC_TYPE_CS_INTERFACE  0x24
#define USB_DESC_TYPE_CS_ENDPOINT   0x25

#define USB_DEVICE_CLASS_MISC       0xEF
#define USB_DEVICE_SUBCLASS_IAD     0x02
#define USB_DEVICE_PROTOCOL_IAD     0x01

#define USB_DEVICE_CLASS_NONE        0x00
#define USB_DEVICE_SUBCLASS_NONE     0x00
#define USB_DEVICE_PROTOCOL_NONE     0x00

// ----------------------------------------
//   CDC device class
// ----------------------------------------
#define USB_DEVICE_CLASS_CDC          0x02
#define USB_DEVICE_SUBCLASS_CDC       0x00
#define USB_DEVICE_PROTOCOL_CDC       0x00

// CDC Subclass Codes
#define USB_INTERFACE_CLASS_CDC       0x02
#define USB_INTERFACE_CLASS_CDC_DATA  0x0A

#define USB_CDC_SUBCLASS_DLCM         0x01
#define USB_CDC_SUBCLASS_ACM          0x02

// CDC  Protocol Codes
#define USB_CDC_PROTOCOL_V250               0x01
#define USB_CDC_PROTOCOL_PCCA_101           0x02
#define USB_CDC_PROTOCOL_PCCA_101_ANNEXO    0x03
#define USB_CDC_PROTOCOL_GSM707             0x04
#define USB_CDC_PROTOCOL_3GPP               0x05
#define USB_CDC_PROTOCOL_CS00170            0x06
#define USB_CDC_PROTOCOL_EEM                0x07

// CDC Descriptor Subtype
#define USB_CDC_DESC_SUBTYPE_HEADER_FUNC     0x00
#define USB_CDC_DESC_SUBTYPE_CALL_MANAGEMENT 0x01
#define USB_CDC_DESC_SUBTYPE_ACM_FUNC        0x02
#define USB_CDC_DESC_SUBTYPE_UNION_FUNC      0x06

// ----------------------------------------
//   Still Inage device class
// ----------------------------------------
#define USB_DEVICE_CLASS_STILL_IMAGE          0x06
#define USB_DEVICE_SUBCLASS_STILL_IMAGE       0x01
#define USB_DEVICE_PROTOCOL_STILL_IMAGE       0x01

// ----------------------------------------
//   MSC device class
// ----------------------------------------
#define USB_DEVICE_CLASS_MSC          0x08
#define USB_DEVICE_SUBCLASS_MSC_SCSI  0x06
#define USB_DEVICE_PROTOCOL_MSC_BOT   0x50 // Bulk-Only Transport

// ----------------------------------------
// UVC device class
// ----------------------------------------
#define USB_DEVICE_CLASS_CODE_UVC     0xEF
#define USB_DEVICE_SUBCLASS_CODE_UVC  0x02
#define USB_DEVICE_PROTOCOL_CODE_UVC  0x01

// UVC Descriptor Length
#define UVC_DESC_LENGTH_VC_INTF         0x0D
#define UVC_DESC_LENGTH_OUTPUT_TERMINAL 0x09
#define UVC_DESC_LENGTH_INPUT_TERMINAL  0x12
#define UVC_DESC_LENGTH_PROCESSING_UNIT 0x0B
#define UVC_DESC_LENGTH_CS_ENDPOINT     0x05
#define UVC_DESC_LENGTH_VS_INPUT_HEADER 0x0E
#define UVC_DESC_LENGTH_VS_MJPEG_FORMAT 0x0B
#define UVC_DESC_LENGTH_VS_MJPEG_FRAME  0x26

// UVC Descriptor Type
#define UVC_DESC_TYPE_CS_UNDEFINED                    0x20
#define UVC_DESC_TYPE_CS_DEVICE                       0x21
#define UVC_DESC_TYPE_CS_CONFIGURATION                0x22
#define UVC_DESC_TYPE_CS_STRING                       0x23
#define UVC_DESC_TYPE_CS_INTF                         0x24
#define UVC_DESC_TYPE_CS_ENDPOINT                     0x25

// UVC Descriptor SubType
#define UVC_DESC_SUBTYPE_VC_HEADER          0x01
#define UVC_DESC_SUBTYPE_VC_INPUT_TERMINAL  0x02
#define UVC_DESC_SUBTYPE_VC_OUTPUT_TERMINAL 0x03
#define UVC_DESC_SUBTYPE_VC_SELECTOR_UNIT   0x04
#define UVC_DESC_SUBTYPE_VC_PROCESSING_UNIT 0x05
#define UVC_DESC_SUBTYPE_VC_EXTENSION_UNIT  0x06
#define UVC_DESC_SUBTYPE_VC_ENCODING_UNIT	0x07

#define UVC_DESC_SUBTYPE_VS_INPUT_HEADER            0x01
#define UVC_DESC_SUBTYPE_VS_OUTPUT_HEADER           0x02
#define UVC_DESC_SUBTYPE_VS_STILL_IMAGE_FRAME       0x03
#define UVC_DESC_SUBTYPE_VS_FORMAT_UNCOMPRESSED     0x04
#define UVC_DESC_SUBTYPE_VS_FRAME_UNCOMPRESSED      0x05
#define UVC_DESC_SUBTYPE_VS_FORMAT_MJPEG            0x06
#define UVC_DESC_SUBTYPE_VS_FRAME_MJPEG             0x07
#define UVC_DESC_SUBTYPE_VS_FORMAT_MPEG2TS          0x0A
#define UVC_DESC_SUBTYPE_VS_FORMAT_DV               0x0C
#define UVC_DESC_SUBTYPE_VS_COLORFORMAT             0x0D
#define UVC_DESC_SUBTYPE_VS_FORMAT_FRAME_BASED      0x10
#define UVC_DESC_SUBTYPE_VS_FRAME_FRAME_BASED       0x11
#define UVC_DESC_SUBTYPE_VS_FORMAT_STREAM_BASED     0x12
#define UVC_DESC_SUBTYPE_VS_FORMAT_H264             0x13
#define UVC_DESC_SUBTYPE_VS_FRAME_H264              0x14
#define UVC_DESC_SUBTYPE_VS_FORMAT_H264_SIMULCAST   0x15
#define UVC_DESC_SUBTYPE_VS_FORMAT_VP8              0x16
#define UVC_DESC_SUBTYPE_VS_FRAME_VP8               0x17
#define UVC_DESC_SUBTYPE_VS_FORMAT_VP8_SIMULCAST    0x18

// Interface class code
#define UVC_INTF_CLASS_CODE_VIDEO               0x0E

// Interface Subclass code
#define UVC_INTF_SUBCLASS_CODE_VIDEO_CONTROL        0x01
#define UVC_INTF_SUBCLASS_CODE_VIDEO_STREAMING      0x02
#define UVC_INTF_SUBCLASS_CODE_IAD                  0x03

// Interface protocol code
#define UVC_INTF_PROTOCOL_CODE_UNDEFINE             0x00
#define UVC_INTF_PROTOCOL_CODE_15                   0x01

// UVC Endpoint Subtype
#define UVC_ENDPOINT_DESC_SUBTYPE_UNDEFINED 0x00
#define UVC_ENDPOINT_DESC_SUBTYPE_GENERAL   0x01
#define UVC_ENDPOINT_DESC_SUBTYPE_ENDPOINT  0x02
#define UVC_ENDPOINT_DESC_SUBTYPE_INTERRUPT 0x03

// UVC Terminal Type
#define UVC_TERMINAL_TYPE_UNDEFINED 0x0100
#define UVC_TERMINAL_TYPE_STREAMING 0x0101
#define UVC_TERMINAL_TYPE_VENDOR_SPECIFIC 0x01FF

// UVC Input Terminal Type
#define UVC_INPUT_TERMINAL_TYPE_VENDOR_SPECIFIC      0x0200
#define UVC_INPUT_TERMINAL_TYPE_CAMERA               0x0201
#define UVC_INPUT_TERMINAL_TYPE_EDIA_TRANSPORT_INPUT 0x0202

// UVC Output Terminal Type
#define UVC_OUTPUT_TERMINAL_TYPE_VENDOR_SPECIFIC     0x0300
#define UVC_OUTPUT_TERMINAL_TYPE_DISPLAY             0x0301
#define UVC_OUTPUT_TERMINAL_TYPE_MEDIA_TRANSPORT     0x0302

// CT control mask
#define UVC_CT_CONTROL_SCANNING_MODE_MASK			0x01
#define UVC_CT_CONTROL_AUTO_EXPOSURE_MODE_MASK		0x02
#define UVC_CT_CONTROL_AUDO_EXPOSURE_PRIORITY_MASK	0x04
#define UVC_CT_CONTROL_EXPOSURE_TIME_ABSOLUTE_MASK	0x08
#define UVC_CT_CONTROL_EXPOSURE_TIME_RELATIVE_MASK	0x10
#define UVC_CT_CONTROL_FOCUS_ABSOLUTE_MASK			0x20
#define UVC_CT_CONTROL_FOCUS_RELATIVE_MASK			0x40
#define UVC_CT_CONTROL_IRIS_ABSOLUTE_MASK			0x80
#define UVC_CT_CONTROL_IRIS_RELATIVE_MASK			0x100
#define UVC_CT_CONTROL_ZOOM_ABSOLUTE_MASK			0x200
#define UVC_CT_CONTROL_ZOOM_RELATIVE_MASK			0x400
#define UVC_CT_CONTROL_PAN_TILE_ABSOLUTE_MASK		0x800
#define UVC_CT_CONTROL_PAN_TILT_RELATIVE_MASK		0x1000
#define UVC_CT_CONTROL_ROLL_ABSOLUTE_MASK			0x2000
#define UVC_CT_CONTROL_ROLL_RELATIVE_MASK			0x4000
#define UVC_CT_CONTROL_RSVD1_MASK					0x8000
#define UVC_CT_CONTROL_RSVD2_MASK					0x10000
#define UVC_CT_CONTROL_FOCUS_AUTO_MASK				0x20000
#define UVC_CT_CONTROL_PRIVACY_MASK					0x40000
#define UVC_CT_CONTROL_RSVD3_MASK					0x80000
#define UVC_CT_CONTROL_RSVD4_MASK					0x100000
#define UVC_CT_CONTROL_RSVD5_MASK					0x200000
#define UVC_CT_CONTROL_RSVD6_MASK					0x400000
#define UVC_CT_CONTROL_RSVD7_MASK					0x800000

// PU control mask
#define UVC_PU_CONTROL_BRIGHTNESS_MASK               0x01
#define UVC_PU_CONTROL_CONTRAST_MASK                 0x02
#define UVC_PU_CONTROL_HUE_MASK                      0x04
#define UVC_PU_CONTROL_SATURATION_MASK               0x08
#define UVC_PU_CONTROL_SHARPNESS_MASK                0x10
#define UVC_PU_CONTROL_GAMMA_MASK                    0x20
#define UVC_PU_CONTROL_WB_TEMPERATURE_MASK           0x40
#define UVC_PU_CONTROL_WB_COMPONENT_MASK             0x80
#define UVC_PU_CONTROL_BACKLIGHT_COMPENSATION_MASK   0x100
#define UVC_PU_CONTROL_GAIN_MASK                     0x200
#define UVC_PU_CONTROL_POWER_LINE_FREQUENCY_MASK     0x400
#define UVC_PU_CONTROL_HUE_AUTO_MASK                 0x800
#define UVC_PU_CONTROL_WB_TEMPERATURE_AUTO_MASK      0x1000
#define UVC_PU_CONTROL_WB_COMPONENT_AUTO_MASK        0x2000
#define UVC_PU_CONTROL_DIGITAL_MULTIPLIER_MASK       0x4000
#define UVC_PU_CONTROL_DIGITAL_MULTIPLIERLIMIT_MASK  0x8000

/* VideoControl Interface Control Selectors */
enum UVC_VC_INTERFACE_CONTROL_SELECTOR {
	UVC_VC_CONTROL_UNDEFINED = 0x00,
	UVC_VC_VIDEO_POWER_MODE_CONTROL,
	UVC_VC_REQUEST_ERROR_CODE_CONTROL,
};

/* VideoStreaming Interface Control Selectors */
enum UVC_VS_INTERFACE_CONTROL_SELECTOR {
	UVC_VS_CONTROL_UNDEFINED = 0x00,
	UVC_VS_PROBE_CONTROL,
	UVC_VS_COMMIT_CONTROL,
	UVC_VS_STILL_PROBE_CONTROL,
	UVC_VS_STILL_COMMIT_CONTROL,
	UVC_VS_STILL_IMAGE_TRIGGER_CONTROL,
	UVC_VS_STREAM_ERROR_CODE_CONTROL,
	UVC_VS_GENERATE_KEY_FRAME_CONTROL,
	UVC_VS_UPDATE_FRAME_SEGMENT_CONTROL,
	UVC_VS_SYNCH_DELAY_CONTROL,
};

/* UVC Camera Terminal Control Selectors */
typedef enum UVC_CAMERA_TERMINAL_CONTROL_SELECTOR_E {
	UVC_CT_CONTROL_UNDEFINED = 0x00,
	UVC_CT_SCANNING_MODE_CONTROL,
	UVC_CT_AE_MODE_CONTROL,
	UVC_CT_AE_PRIORITY_CONTROL,
	UVC_CT_EXPOSURE_TIME_ABSOLUTE_CONTROL,
	UVC_CT_EXPOSURE_TIME_RELATIVE_CONTROL,
	UVC_CT_FOCUS_ABSOLUTE_CONTROL,
	UVC_CT_FOCUS_RELATIVE_CONTROL,
	UVC_CT_FOCUS_AUTO_CONTROL,
	UVC_CT_IRIS_ABSOLUTE_CONTROL,
	UVC_CT_IRIS_RELATIVE_CONTROL,
	UVC_CT_ZOOM_ABSOLUTE_CONTROL,
	UVC_CT_ZOOM_RELATIVE_CONTROL,
	UVC_CT_PANTILT_ABSOLUTE_CONTROL,
	UVC_CT_PANTILT_RELATIVE_CONTROL,
	UVC_CT_ROLL_ABSOLUTE_CONTROL,
	UVC_CT_ROLL_RELATIVE_CONTROL,
	UVC_CT_PRIVACY_CONTROL,
	UVC_CT_FOCUS_SIMPLE_CONTROL,
	UVC_CT_WINDOW_CONTROL,
	UVC_CT_REGION_OF_INTEREST_CONTROL,
	UVC_CT_NUMBER,
} UVC_CAMERA_TERMINAL_CONTROL_SELECTOR;

/* UVC Processing Unit Control Selectors */
typedef enum UVC_PROCESSING_UNIT_CONTROL_SELECTOR_E {
	UVC_PU_CONTROL_UNDEFINED = 0x00,
	UVC_PU_BACKLIGHT_COMPENSATION_CONTROL,
	UVC_PU_BRIGHTNESS_CONTROL,
	UVC_PU_CONTRAST_CONTROL,
	UVC_PU_GAIN_CONTROL,
	UVC_PU_POWER_LINE_FREQUENCY_CONTROL,
	UVC_PU_HUE_CONTROL,
	UVC_PU_SATURATION_CONTROL,
	UVC_PU_SHARPNESS_CONTROL,
	UVC_PU_GAMMA_CONTROL,
	UVC_PU_WHITE_BALANCE_TEMPERATURE_CONTROL,
	UVC_PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL,
	UVC_PU_WHITE_BALANCE_COMPONENT_CONTROL,
	UVC_PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL,
	UVC_PU_DIGITAL_MULTIPLIER_CONTROL,
	UVC_PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL,
	UVC_PU_HUE_AUTO_CONTROL,
	UVC_PU_ANALOG_VIDEO_STANDARD_CONTROL,
	UVC_PU_ANALOG_LOCK_STATUS_CONTROL,
	UVC_PU_PU_CONTRAST_AUTO_CONTROL,
	UVC_PU_NUMBER,
} UVC_PROCESSING_UNIT_CONTROL_SELECTOR;

/* UVC 1.1 Extension Unit Control Selectors */
typedef enum UVC_EXTENSION_UNIT_H264_CONTROL_SELECTOR_E {
	UVC_XU_H264_CONTROL_UNDEFINED = 0x00,
	UVC_XU_H264_CONFIG_PROBE,
	UVC_XU_H264_CONFIG_COMMIT,
	UVC_XU_H264_RATE_CONTROL_MODE,
	UVC_XU_H264_TEMPORAL_SCALE_MODE,
	UVC_XU_H264_SPATIAL_SCALE_MODE,
	UVC_XU_H264_SNR_SCALE_MODE,
	UVC_XU_H264_LTR_BUFFER_SIZE_CONTROL,
	UVC_XU_H264_LTR_PICTURE_CONTROL,
	UVC_XU_H264_PICTURE_TYPE_CONTROL,
	UVC_XU_H264_VERSION,
	UVC_XU_H264_ENCODER_RESET,
	UVC_XU_H264_FRAMERATE_CONFIG,
	UVC_XU_H264_VIDEO_ADVANCE_CONFIG,
	UVC_XU_H264_BITRATE_LAYERS,
	UVC_XU_H264_QP_STEPS_LAYERS,
	UVC_XU_H264_NUMBER,
} UVC_EXTENSION_UNIT_H264_CONTROL_SELECTOR;

typedef enum UVC_EXTENSION_UNIT_H264_VIDEO_CONFIG_E {
	UVCX_VIDEO_CONFIG_UNDEFINED = 0,
	UVCX_VIDEO_CONFIG_FRAME_INTERVAL,
	UVCX_VIDEO_CONFIG_BIT_RATE,
	UVCX_VIDEO_CONFIG_HINTS,
	UVCX_VIDEO_CONFIG_CONFIG_INDEX,
	UVCX_VIDEO_CONFIG_WIDTH,
	UVCX_VIDEO_CONFIG_HEIGHT,
	UVCX_VIDEO_CONFIG_SLICE_UNIT,
	UVCX_VIDEO_CONFIG_SLICE_MODE,
	UVCX_VIDEO_CONFIG_PROFILE,
	UVCX_VIDEO_CONFIG_I_FRAME_PERIOD,
	UVCX_VIDEO_CONFIG_ESTIMATE_VIDEO_DELAY,
	UVCX_VIDEO_CONFIG_ESTIMATE_MAX_CONFIG_DELAY,
	UVCX_VIDEO_CONFIG_USAGE_TYPE,
	UVCX_VIDEO_CONFIG_RATE_CONTROL_MODE,
	UVCX_VIDEO_CONFIG_TEMPORAL_SCALE_MODE,
	UVCX_VIDEO_CONFIG_SPATIAL_SCALE_MODE,
	UVCX_VIDEO_CONFIG_SNR_SCALE_MODE,
	UVCX_VIDEO_CONFIG_STREAM_MUX_OPTION,
	UVCX_VIDEO_CONFIG_STREAM_FORMAT,
	UVCX_VIDEO_CONFIG_ENTROPY_CABAC,
	UVCX_VIDEO_CONFIG_TIME_STAMP,
	UVCX_VIDEO_CONFIG_NUM_OF_RECORD_FRAME,
	UVCX_VIDEO_CONFIG_PREVIEW_FLIP,
	UVCX_VIDEO_CONFIG_VIEW,
	UVCX_VIDEO_CONFIG_RESERVE1,
	UVCX_VIDEO_CONFIG_RESERVE2,
	UVCX_VIDEO_CONFIG_STREAM_ID,
	UVCX_VIDEO_CONFIG_SPATIAL_LAYER_RATIO,
	UVCX_VIDEO_CONFIG_LEAKY_BUCKET_SIZE,

	UVCX_VIDEO_CONFIG_NUMBER,
} UVC_EXTENSION_UNIT_H264_VIDEO_CONFIG;

/* bRateControlMode defines */
#define RATECONTROL_CBR           0x01
#define RATECONTROL_VBR           0x02
#define RATECONTROL_CONST_QP      0x03
#define RATECONTROL_FIXED_FRM_FLG 0x10

/* bStreamFormat defines */
#define STREAMFORMAT_ANNEXB       0x00
#define STREAMFORMAT_NAL          0x01

/* bEntropyCABAC defines */
#define ENTROPY_CAVLC             0x00
#define ENTROPY_CABAC             0x01

/* bTimingstamp defines */
#define TIMESTAMP_SEI_DISABLE     0x00
#define TIMESTAMP_SEI_ENABLE      0x01

/* bPreviewFlipped defines */
#define PREFLIPPED_DISABLE        0x00
#define PREFLIPPED_HORIZONTAL     0x01

/* wPictureType defines */
#define PICTURE_TYPE_IFRAME 	0x0000 //Generate an IFRAME
#define PICTURE_TYPE_IDR		0x0001 //Generate an IDR
#define PICTURE_TYPE_IDR_FULL	0x0002 //Generate an IDR frame with new SPS and PPS

/* bStreamMuxOption defines */
#define STREAMMUX_H264          (1 << 0) | (1 << 1)
#define STREAMMUX_YUY2          (1 << 0) | (1 << 2)
#define STREAMMUX_YUYV          (1 << 0) | (1 << 2)
#define STREAMMUX_NV12          (1 << 0) | (1 << 3)

/* UVC 1.5 Encoding Unit Control Selectors */
typedef enum UVC_ENCODING_UNIT_CONTROL_SELECTOR_E {
	UVC_EU_CONTROL_UNDEFINED = 0x00,
	UVC_EU_SELECT_LAYER_CONTROL,
	UVC_EU_PROFILE_TOOLSET_CONTROL,
	UVC_EU_VIDEO_RESOLUTION_CONTROL,
	UVC_EU_MIN_FRAME_INTERVAL_CONTROL,
	UVC_EU_SLICE_MODE_CONTROL,
	UVC_EU_RATE_CONTROL_MODE_CONTROL,
	UVC_EU_AVERAGE_BITRATE_CONTROL,
	UVC_EU_CPB_SIZE_CONTROL,
	UVC_EU_PEAK_BIT_RATE_CONTROL,
	UVC_EU_QUANTIZATION_PARAMS_CONTROL,
	UVC_EU_SYNC_REF_FRAME_CONTROL,
	UVC_EU_LTR_BUFFER_CONTROL,
	UVC_EU_LTR_PICTURE_CONTROL,
	UVC_EU_LTR_VALIDATION_CONTROL,
	UVC_EU_LEVEL_IDC_LIMIT_CONTROL,
	UVC_EU_SEI_PAYLOADTYPE_CONTROL,
	UVC_EU_QP_RANGE_CONTROL,
	UVC_EU_PRIORITY_CONTROL,
	UVC_EU_START_OR_STOP_LAYER_CONTROL,
	UVC_EU_ERROR_RESILIENCY_CONTROL,
	UVC_EU_NUMBER,
} UVC_ENCODING_UNIT_CONTROL_SELECTOR;

/* Video Class-Specific Request Code */
typedef enum UVC_REQUEST_CODE_E {
	UVC_SET_CUR = 0x01,
	UVC_SET_CUR_ALL = 0x11,
	UVC_GET_CUR = 0x81,
	UVC_GET_MIN = 0x82,
	UVC_GET_MAX = 0x83,
	UVC_GET_RES = 0x84,
	UVC_GET_LEN = 0x85,
	UVC_GET_INFO = 0x86,
	UVC_GET_DEF = 0x87,
	GET_CUR_ALL = 0x91,
	GET_MIN_ALL = 0x92,
	GET_MAX_ALL = 0x93,
	GET_RES_ALL = 0x94,
	GET_DEF_ALL = 0x97
} UVC_REQUEST_CODE;

/* VideoControl Error Code */
typedef enum UVC_VC_ERROR_CODE_E {
    UVC_VC_ER_CD_NO_ERROR = 0x00,
    UVC_VC_ER_CD_NOT_READY,
    UVC_VC_ER_CD_WRONG_STATE,
    UVC_VC_ER_CD_POWER,
    UVC_VC_ER_CD_OUT_OF_RANGE,
    UVC_VC_ER_CD_INVALID_UNIT,
    UVC_VC_ER_CD_INVALID_CONTROL,
    UVC_VC_ER_CD_INVALID_REQUEST,
    UVC_VC_ER_CD_UNKNOWN = 0xFF
} UVC_VC_ERROR_CODE;

#endif  /* _STD_USB_H_ */
