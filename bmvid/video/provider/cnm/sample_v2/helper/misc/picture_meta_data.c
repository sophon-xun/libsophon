/* 
 * Copyright (c) 2018, Chips&Media
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <assert.h>
#include <string.h>
#include "main_helper.h"

osal_file_t * CreatePicInfoXmlFile(
    const char *yuvPath
    )
{
    char strXmlFilePath[256];
    osal_file_t *fp;

    if (yuvPath != NULL) {
        osal_sprintf(strXmlFilePath, "%s.xml", yuvPath);
    }
    else {
        osal_strcpy(strXmlFilePath, "out.xml");
    }
    if ((fp=osal_fopen(strXmlFilePath, "wb")) == NULL) {
        osal_printf("%s:%d failed to open %s\n", __FUNCTION__, __LINE__, strXmlFilePath);
        return NULL;
    }

    osal_fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n",fp);
    osal_fputs("<ffprobe>\r\n", fp);
    osal_fputs("<frames>\r\n", fp);

    return fp;
}

void ClosePicInfoXMLFile(
    osal_file_t *fpXML
    )
{
    if (fpXML != NULL) {
        osal_fputs("</frames>\r\n", fpXML);
        osal_fputs("</ffprobe>\r\n", fpXML);

        osal_fclose(fpXML);
    }
}

void SavePicInfoToXml(
    osal_file_t*           fpXml, 
    DecOutputInfo*  fbInfo
    )
{
    //BOOL bCrop;
    BOOL   bKeyFrame;
    Uint32 pkt_pts;
    Uint32 pkt_dts;
    Uint32 pkt_pos;
    double pkt_pts_sec;
    double pkt_dts_sec;
    Uint32 pkt_size;
    Uint32 width;
    Uint32 height;
    Uint32 bitdepthY;
    Uint32 bitdepthC;
    char   strFormat[256] = {"yuv420p"};
    char   strPicType[8];

    pkt_size = fbInfo->consumedByte;
    pkt_pos = 0;
    pkt_size = 0;
    pkt_pts = 0;
    pkt_dts = 0;
    pkt_pts_sec = pkt_pts/1000.0;
    pkt_dts_sec = pkt_dts/1000.0;
    bKeyFrame = FALSE;
    switch(fbInfo->picType) {
    case PIC_TYPE_I:
        osal_strcpy(strPicType, "I");
        bKeyFrame = TRUE;
        break;
    case PIC_TYPE_P:
        osal_strcpy(strPicType, "P");
        break;
    case PIC_TYPE_B:
        osal_strcpy(strPicType, "B");
        break;
    default:
        osal_strcpy(strPicType, "B");
        break;
    }

    if (fbInfo->dispFrame.format == FORMAT_420) {
        if (fbInfo->dispFrame.cbcrInterleave == TRUE) {
            osal_strcpy(strFormat, "nv12");
        }
        else {
            osal_strcpy(strFormat, "yuv420p");
        }

        if (fbInfo->dispFrame.nv21 == TRUE) {
            osal_strcpy(strFormat, "nv21");
        }
    }

    width     = fbInfo->dispPicWidth;
    height    = fbInfo->dispPicHeight;
    bitdepthY = fbInfo->dispFrame.lumaBitDepth;
    bitdepthC = fbInfo->dispFrame.chromaBitDepth;

    osal_fprintf(fpXml, "<frame media_type=\"video\" key_frame=\"%d\" pkt_pts=\"%d\" pkt_pts_time=\"%.1f\" "
                   "pkt_dts=\"%d\" pkt_dts_time=\"%.1f\" pkt_pos=\"%d\" pkt_size=\"%d\" width=\"%d\" "
                   "height=\"%d\" pix_fmt=\"%s\" pict_type=\"%s\" coded_picture_number=\"0\" display_picture_number=\"0\""
                   "interlaced_frame=\"0\" top_field_first=\"0\" repeat_pict=\"0\" bitdepthY=\"%d\" bitdepthC=\"%d\"/>\r\n", 
            bKeyFrame, pkt_pts, pkt_pts_sec, pkt_dts, pkt_dts_sec, pkt_pos, pkt_size, width, height, strFormat, strPicType, bitdepthY, bitdepthC);
    osal_fflush(fpXml);

    return;
}
 
