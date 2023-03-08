#ifndef __APP_IPCAM_VENC_H__
#define __APP_IPCAM_VENC_H__

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include "cvi_comm_video.h"
#include "cvi_comm_sys.h"
#include "cvi_venc.h"
#include "app_ipcam_mq.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define VENC_CHN_MAX	8

typedef enum APP_NEED_STOP_MODULE_T {
    APP_NEED_STOP_NULL   = 0x00,
    APP_NEED_STOP_RTSP   = 0x01,
    APP_NEED_STOP_STREAM = 0x02,
    APP_NEED_STOP_ALL    = 0xFF
} APP_NEED_STOP_MODULE_E;

typedef enum APP_VENC_CHN_T {
    APP_VENC_1ST = 0x01,
    APP_VENC_2ND = 0x02,
    APP_VENC_3RD = 0x04,
    APP_VENC_4TH = 0x08,
    APP_VENC_5TH = 0x10,
    APP_VENC_6TH = 0x20,
    APP_VENC_7TH = 0x40,
    APP_VENC_8TH = 0x80,
    APP_VENC_ALL = 0xFF
} APP_VENC_CHN_E;

#define APP_IPCAM_STREAM_ID_TO_CHN(SID) do {    \
    if (SID == 0) SID = APP_VENC_1ST;           \
    else if (SID == 1) SID = APP_VENC_2ND;      \
    else if (SID == 2) SID = APP_VENC_3RD;      \
    else if (SID == 3) SID = APP_VENC_4TH;      \
    else if (SID == 4) SID = APP_VENC_5TH;      \
    else if (SID == 5) SID = APP_VENC_6TH;      \
    else if (SID == 6) SID = APP_VENC_7TH;      \
    else if (SID == 7) SID = APP_VENC_8TH;      \
    else SID = APP_VENC_ALL;                    \
} while (0)

typedef enum APP_RC_MODE_T {
    APP_RC_CBR = 0,
    APP_RC_VBR,
    APP_RC_AVBR,
    APP_RC_QVBR,
    APP_RC_FIXQP,
    APP_RC_QPMAP,
    APP_RC_MAX
} APP_RC_MODE_E;

typedef struct APP_REF_PARAM_T {
    CVI_S32 tempLayer;
} APP_REF_PARAM_S;

typedef struct APP_CU_PREDI_PARAM_T {
    CVI_U32 u32IntraCost;
} APP_CU_PREDI_PARAM_S;

typedef struct APP_FRAMELOST_PARAM_T {
    CVI_S32 frameLost;
    CVI_U32 frameLostGap;
    CVI_U32 frameLostBspThr;
} APP_FRAMELOST_PARAM_S;

typedef struct APP_H264_ENTROPY_PARAM_T {
    CVI_U32 h264EntropyMode;
} APP_H264_ENTROPY_PARAM_S;

typedef struct APP_H264_TRANS_PARAM_T{
    CVI_S32 h264ChromaQpOffset;
} APP_H264_TRANS_PARAM_S;

typedef struct APP_H264_VUI_PARAM_T{
    CVI_U8	aspectRatioInfoPresentFlag;
    CVI_U8	aspectRatioIdc;
    CVI_U16	sarWidth;
    CVI_U16	sarHeight;
    CVI_U8	overscanInfoPresentFlag;
    CVI_U8	overscanAppropriateFlag;
    CVI_U8	timingInfoPresentFlag;
    CVI_U8	fixedFrameRateFlag;
    CVI_U32	numUnitsInTick;
    CVI_U32	timeScale;
    CVI_U8	videoSignalTypePresentFlag;
    CVI_U8	videoFormat;
    CVI_U8	videoFullRangeFlag;
    CVI_U8	colourDescriptionPresentFlag;
    CVI_U8	colourPrimaries;
    CVI_U8	transferCharacteristics;
    CVI_U8	matrixCoefficients;
} APP_H264_VUI_PARAM_S;

typedef struct APP_H265_TRANS_PARAM_T{
    CVI_S32 h265CbQpOffset;
    CVI_S32 h265CrQpOffset;
} APP_H265_TRANS_PARAM_S;

typedef struct APP_H265_VUI_PARAM_T{
    CVI_U8	aspectRatioInfoPresentFlag;
    CVI_U8	aspectRatioIdc;
    CVI_U16	sarWidth;
    CVI_U16	sarHeight;
    CVI_U8	overscanInfoPresentFlag;
    CVI_U8	overscanAppropriateFlag;
    CVI_U8	timingInfoPresentFlag;
    CVI_U8	fixedFrameRateFlag;
    CVI_U32	numUnitsInTick;
    CVI_U32	timeScale;
    CVI_U8	videoSignalTypePresentFlag;
    CVI_U8	videoFormat;
    CVI_U8	videoFullRangeFlag;
    CVI_U8	colourDescriptionPresentFlag;
    CVI_U8	colourPrimaries;
    CVI_U8	transferCharacteristics;
    CVI_U8	matrixCoefficients;
} APP_H265_VUI_PARAM_S;

typedef struct APP_JPEG_CODEC_PARAM_T {
    CVI_S32 quality;
    CVI_S32 MCUPerECS;
} APP_JPEG_CODEC_PARAM_S;

typedef union APP_GOP_PARAM_N {
    VENC_GOP_NORMALP_S stNormalP; /*attributes of normal P*/
    VENC_GOP_DUALP_S stDualP; /*attributes of dual   P*/
    VENC_GOP_SMARTP_S stSmartP; /*attributes of Smart P*/
    VENC_GOP_ADVSMARTP_S stAdvSmartP; /*attributes of AdvSmart P*/
    VENC_GOP_BIPREDB_S stBipredB; /*attributes of b */
} APP_GOP_PARAM_U;

/* APP_RC_PARAM_S copy from VENC_RC_PARAM_S */
typedef struct APP_RC_PARAM_T {
    CVI_U32 u32ThrdI[RC_TEXTURE_THR_SIZE];
    CVI_U32 u32ThrdP[RC_TEXTURE_THR_SIZE];
    CVI_U32 u32ThrdB[RC_TEXTURE_THR_SIZE];
    CVI_U32 u32DirectionThrd;
    CVI_U32 u32RowQpDelta;
    CVI_S32 s32FirstFrameStartQp;
    CVI_S32 s32InitialDelay;
    CVI_U32 u32ThrdLv;
    CVI_BOOL bBgEnhanceEn;
    CVI_S32 s32BgDeltaQp;
    CVI_S32 s32ChangePos;
    CVI_U32 u32MinIprop;
    CVI_U32 u32MaxIprop;
    CVI_S32 s32MaxReEncodeTimes;
    CVI_S32 s32MinStillPercent;
    CVI_U32 u32MaxStillQP;
    CVI_U32 u32MinStillPSNR;
    CVI_U32 u32MaxQp;
    CVI_U32 u32MinQp;
    CVI_U32 u32MaxIQp;
    CVI_U32 u32MinIQp;
    CVI_U32 u32MinQpDelta;
    CVI_U32 u32MotionSensitivity;
    CVI_S32	s32AvbrFrmLostOpen;
    CVI_S32 s32AvbrFrmGap;
    CVI_S32 s32AvbrPureStillThr;
    CVI_BOOL bQpMapEn;
    VENC_RC_QPMAP_MODE_E enQpMapMode;
} APP_RC_PARAM_S;

typedef struct APP_VENC_CHN_CFG_T {
    CVI_BOOL bEnable;   /* set by param_config.ini , DO NOT update by coding */
    CVI_BOOL bStart;
    VENC_CHN VencChn;
    PAYLOAD_TYPE_E enType;
    CVI_U32 StreamTo;
    CVI_U32 u32Duration;
    CVI_BOOL bRtspEn;
    CVI_U32 u32Width;
    CVI_U32 u32Height;
    CVI_U32 u32SrcFrameRate;
    CVI_U32 fr32DstFrameRate;
    CVI_U32 u32BitRate;
    CVI_U32 u32MaxBitRate;
    CVI_U32 VpssGrp;
    CVI_U32 VpssChn;
    CVI_U32 u32Profile;
    CVI_BOOL bSingleCore;
    CVI_U32 u32Gop;
    CVI_U32 u32IQp;
    CVI_U32 u32PQp;
    CVI_U32 statTime;
    CVI_U32 enBindMode;
    MMF_CHN_S astChn[2];
    VENC_GOP_MODE_E enGopMode;
    APP_GOP_PARAM_U unGopParam;
    VENC_RC_MODE_E enRcMode;
    APP_RC_PARAM_S stRcParam;
    APP_JPEG_CODEC_PARAM_S stJpegCodecParam;
    FILE *pFile;
    CVI_U32 frameNum;
    CVI_U32 fileNum;
    CVI_CHAR SavePath[32];
    volatile CVI_S32 savePic;
} APP_VENC_CHN_CFG_S;

typedef struct APP_PARAM_VENC_CTX_T {
    CVI_BOOL bInit;
    CVI_S32 s32VencChnCnt;
    APP_VENC_CHN_CFG_S astVencChnCfg[VENC_CHN_MAX];
} APP_PARAM_VENC_CTX_S;

APP_PARAM_VENC_CTX_S *app_ipcam_Venc_Param_Get(void);
APP_VENC_CHN_CFG_S *app_ipcam_VencChnCfg_Get(VENC_CHN VencChn);
int app_ipcam_Venc_Init(APP_VENC_CHN_E VencIdx);
int app_ipcam_Venc_Start(APP_VENC_CHN_E VencIdx);
int app_ipcam_Venc_Stop(APP_VENC_CHN_E VencIdx);
void app_ipcam_JpgCapFlag_Set(CVI_BOOL bEnable);
int app_ipcam_VencSize_Set(void);

/*****************************************************************
 *  The following API for command test used             S
 * **************************************************************/
int app_ipcam_CmdTask_VideoAttr_Set(CVI_MQ_MSG_t *msg, CVI_VOID *userdate);
/*****************************************************************
 *  The above API for command test used                 E
 * **************************************************************/

#ifdef __cplusplus
}
#endif

#endif
