/**
* @file bm_video_internal.h
* @author
* @brief This module contains the interface definition for bm1682 video decoder component.
*/
#ifndef BM_VIDEO_INTERNAL_H
#define BM_VIDEO_INTERNAL_H

#include "vpuapi.h"
#include "main_helper.h"
#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)
#include<stdbool.h>
#endif
#include "bmlib_runtime.h"
#include "bm_video_interface.h"

typedef enum {
    BMDEC_START_CREATE,
    BMDEC_START_LOAD,
    BMDEC_START_INIT,
    BMDEC_START_DECODING,
    BMDEC_START_REWIND,
    BMDEC_START_GET_ALLFRAME,
    BMDEC_START_FLUSH,
    BMDEC_START_ENDOF,
    BMDEC_START_STOP,
    BMDEC_START_CLOSE,
} BMDecStartStatus;

typedef struct BMVidDecConfig_struct {
    Uint32              magicNumber;
    Int32               forceOutNum;
    Int32               bitFormat;
    Int32               reorder;
    TiledMapType        mapType;
    Int32               bitstreamMode;
    BOOL                enableWTL;
    FrameFlag           wtlMode;
    FrameBufferFormat   wtlFormat;
    Int32               coreIdx;
    Int32               instIdx;
    BOOL                enableCrop;                 //!<< option for saving yuv
    Uint32              loopCount;
    BOOL                cbcrInterleave;             //!<< 0: None, 1: NV12, 2: NV21
    BOOL                nv21;                       //!<< FALSE: NV12, TRUE: NV21,
                                                    //!<< This variable is valid when cbcrInterleave is TRUE
    EndianMode          streamEndian;
    EndianMode          frameEndian;
    Int32               secondaryAXI;
    Int32               compareType;
    BOOL                thumbnailMode;
    Int32               skipMode;
    struct {
        BOOL        enableMvc;                      //!<< H.264 MVC
        BOOL        enableTiled2Linear;
        FrameFlag   tiled2LinearMode;
        BOOL        enableBWB;
        Uint32      rotate;                         //!<< 0, 90, 180, 270
        Uint32      mirror;
        BOOL        enableDering;                   //!<< MPEG-2/4
        BOOL        enableDeblock;                  //!<< MPEG-2/4
        Uint32      mp4class;                       //!<< MPEG_4
        Uint32      frameCacheBypass;
        Uint32      frameCacheBurst;
        Uint32      frameCacheMerge;
        Uint32      frameCacheWayShape;
        LowDelayInfo    lowDelay;                   //!<< H.264
    } coda9;
    struct {
        Uint32      numVCores;                      //!<< This numVCores is valid on PRODUCT_ID_4102 multi-core version
        Uint32      fbcMode;
        BOOL        bwOptimization;                 //!<< On/Off bandwidth optimization function
        BOOL        craAsBla;
    } wave;
    BOOL            enableUserData;
    Uint32          testEnvOptions;             /*!<< See debug.h */
} BMVidDecConfig;

typedef struct BMVidExtraInfo {
    int isFill;
    int colorPrimaries;
    int colorTransferCharacteristic;
    int colorSpace;
    int colorRange;
    int chromaLocation;
} BMVidExtraInfo;

typedef struct BMVidCodInst {
    DecHandle codecInst;
    bm_device_mem_t vbStream;
    bm_device_mem_t vbUserData;
    volatile Uint32 seqInitFlag;
    volatile Uint32 isStreamBufFilled;
    volatile BMDecStatus decStatus;
    BMVidDecConfig decConfig;
    Queue* ppuQ;
    Queue* displayQ;
    Queue* freeQ;
    bm_device_mem_t        pFbMem[MAX_REG_FRAME];
    Uint64                 fbMemVaddr[MAX_REG_FRAME];
    bm_device_mem_t        pPPUFbMem[MAX_REG_FRAME];
    Uint64                 pPUFbMemVaddr[MAX_REG_FRAME];
    volatile int endof_flag;
    Queue* inputQ;
    osal_cond_t inputCond;
    osal_cond_t outputCond;
    BOOL enablePPU;
    volatile int frameInBuffer;
    Uint32 sizeInWord;
    Uint16 *pusBitCode;
    Queue* inputQ2;
    Queue* sequenceQ;
    PhysicalAddress streamWrAddr;
#ifdef __linux__
    sem_t* vid_open_sem;
#elif _WIN32
    HANDLE* vid_open_sem;
#endif
    osal_thread_t processThread;
    Uint32 remainedSize;
    FrameBuffer pPPUFrame[MAX_REG_FRAME];
    int PPUFrameNum;
    int extraFrameBufferNum;
    FILE *fp_stream;
    int dump_frame_num;
    int file_flag;
    int no_reorder_flag;
    int enable_cache;
    BMVidExtraInfo extraInfo;
    //bm_handle_t devHandles;
    int64_t total_time;
    int64_t max_time;
    int64_t min_time;
    int64_t dec_idx;
    int perf;
    BMVidFrame cache_bmframe[32];
} BMVidCodInst;

typedef struct PkgInfo {
    u64 rd;
    int len;
    int flag;
    u64 pts;
    u64 dts;
} PkgInfo;

typedef struct BMVidCodInst* BMVidHandle;

typedef struct {
    DecGetFramebufInfo  fbInfo;
    bm_device_mem_t        allocFbMem[MAX_REG_FRAME];
} SequenceMemInfo;

int BMVidDecCreateW5(BMVidCodHandle *pVidCodHandle, BMVidDecParam *decParam);

void bm_syscxt_init(void *p_dec_param, BMVidCodHandle vidHandle);
int  bm_syscxt_status(int coreid, int instid, int pos);
int  bm_syscxt_chkstatus(int coreid);
void bm_syscxt_statusLock(int coreid);
void bm_syscxt_statusUnlock(int coreid);
void bm_syscxt_status_wakeup(int coreid);
#endif
