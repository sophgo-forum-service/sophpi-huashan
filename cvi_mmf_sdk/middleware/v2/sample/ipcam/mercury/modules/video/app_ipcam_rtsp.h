#ifndef __APP_IPCAM_RTSP_H__
#define __APP_IPCAM_RTSP_H__

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
#include <pthread.h>
#include "cvi_type.h"
#include "cvi_common.h"
#include "rtsp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_RTSP_SESSION     6

#define APP_RTSP_VCODEC_CHK(S_C,D_C) do {                   \
        if (S_C == PT_H265) D_C = RTSP_VIDEO_H265;          \
        else if (S_C == PT_H264) D_C = RTSP_VIDEO_H264;     \
        else if (S_C == PT_MJPEG) D_C = RTSP_VIDEO_JPEG;    \
        else {                                              \
            D_C = RTSP_VIDEO_NONE;                          \
            printf("\033[40;31m S_Codec(%d) not match D_Codec(%d) \033[0m\n", S_C, D_C);  \
            return CVI_FAILURE;                             \
        }                                                   \
} while(0)

typedef struct APP_PARAM_RTSP_S {
    CVI_S32 session_cnt;
    CVI_S32 port;
    CVI_BOOL bStart[MAX_RTSP_SESSION];
    VENC_CHN VencChn[MAX_RTSP_SESSION];
    CVI_RTSP_SESSION *pstSession[MAX_RTSP_SESSION];
    CVI_RTSP_SESSION_ATTR SessionAttr[MAX_RTSP_SESSION];
    CVI_RTSP_STATE_LISTENER listener;
    CVI_RTSP_CTX *pstServerCtx;
} APP_PARAM_RTSP_T;

APP_PARAM_RTSP_T *app_ipcam_Rtsp_Param_Get(void);
int app_ipcam_Rtsp_Server_Create(CVI_VOID);
int app_ipcam_rtsp_Server_Destroy(CVI_VOID);

#ifdef __cplusplus
}
#endif

#endif
