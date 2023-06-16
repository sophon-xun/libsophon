/* Simplified API for JPEG en- and decoding with the BitMain SoC
 * Copyright (C) 2018 Solan Shang
 * Copyright (C) 2014 Carlos Rafael Giani
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */


#include <string.h>
#ifndef  _WIN32
#include <pthread.h>
#endif
#include "bmjpuapi_jpeg.h"
#include "bmjpuapi_priv.h"
#define BS_MASK (1024*16-1)

#define HEAP_0_1_2  (0x7)
#define HEAP_1_2    (0x6)

static unsigned long int get_cur_threadid(){
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}

/******************
 ** JPEG DECODER **
 ******************/

static int initial_info_callback(BmJpuDecoder *decoder, BmJpuDecInitialInfo *new_initial_info, unsigned int output_code, void *user_data);
static BmJpuDecReturnCodes bm_jpu_jpeg_dec_deallocate_framebuffers(BmJpuJPEGDecoder *jpeg_decoder);


static int initial_info_callback(BmJpuDecoder *decoder, BmJpuDecInitialInfo *new_initial_info, unsigned int output_code, void *user_data)
{
    unsigned int i;
    int iret = 0;
    BmJpuDecReturnCodes ret;
    bm_status_t  bmlib_ret = BM_SUCCESS;
    BmJpuJPEGDecoder *jpeg_decoder = (BmJpuJPEGDecoder *)user_data;
    int frame_width, frame_height;

    BMJPUAPI_UNUSED_PARAM(decoder);
    BMJPUAPI_UNUSED_PARAM(output_code);

    ret = bm_jpu_jpeg_dec_deallocate_framebuffers(jpeg_decoder);
    if (ret != BM_JPU_DEC_RETURN_CODE_OK) {
        return 0;
    }

    jpeg_decoder->initial_info = *new_initial_info;
    frame_width = new_initial_info->frame_width;
    frame_height = new_initial_info->frame_height;
    if (new_initial_info->roiFrameWidth && new_initial_info->roiFrameHeight){
        if (new_initial_info->roiFrameWidth < new_initial_info->frame_width)
            frame_width = new_initial_info->roiFrameWidth;
        if (new_initial_info->roiFrameHeight < new_initial_info->frame_height)
            frame_height = new_initial_info->roiFrameHeight;
    }
    BM_JPU_DEBUG(
        "initial info:  size: %ux%u min num required framebuffers: %u  framebuffer alignment: %u  color format: %s  chroma interleave: %d",
        new_initial_info->frame_width,
        new_initial_info->frame_height,
        new_initial_info->min_num_required_framebuffers,
        new_initial_info->framebuffer_alignment,
        bm_jpu_color_format_string(new_initial_info->color_format),
        new_initial_info->chroma_interleave
    );

    jpeg_decoder->num_framebuffers = new_initial_info->min_num_required_framebuffers + jpeg_decoder->num_extra_framebuffers;

    iret = bm_jpu_calc_framebuffer_sizes(new_initial_info->color_format,
                                  frame_width,
                                  frame_height,
                                  new_initial_info->framebuffer_alignment,
                                  new_initial_info->chroma_interleave,
                                  &(jpeg_decoder->calculated_sizes));
    if (iret != BM_JPU_DEC_RETURN_CODE_OK) {
        return 0;
    }
    BM_JPU_DEBUG(
        "calculated sizes:  frame width&height: %dx%d  Y stride: %u  CbCr stride: %u  Y size: %u  CbCr size: %u  total size: %u",
        jpeg_decoder->calculated_sizes.aligned_frame_width, jpeg_decoder->calculated_sizes.aligned_frame_height,
        jpeg_decoder->calculated_sizes.y_stride, jpeg_decoder->calculated_sizes.cbcr_stride,
        jpeg_decoder->calculated_sizes.y_size, jpeg_decoder->calculated_sizes.cbcr_size,
        jpeg_decoder->calculated_sizes.total_size
    );

    jpeg_decoder->framebuffers  = BM_JPU_ALLOC(sizeof(BmJpuFramebuffer) * jpeg_decoder->num_framebuffers);
    jpeg_decoder->fb_dmabuffers = BM_JPU_ALLOC(sizeof(bm_device_mem_t) * jpeg_decoder->num_framebuffers);

    bm_handle_t handle = bm_jpu_get_handle(jpeg_decoder->device_index);
    for (i = 0; i < jpeg_decoder->num_framebuffers; ++i)
    {
        bmlib_ret = bm_malloc_device_byte_heap_mask(handle, &(jpeg_decoder->fb_dmabuffers[i]), HEAP_1_2, jpeg_decoder->calculated_sizes.total_size);
        if (bmlib_ret != BM_SUCCESS)
        {
            BM_JPU_ERROR("could not allocate DMA buffer for framebuffer #%u. id=%lu",
                         i, get_cur_threadid());
            goto error;
        }

        iret = bm_jpu_fill_framebuffer_params(&(jpeg_decoder->framebuffers[i]), &(jpeg_decoder->calculated_sizes), &(jpeg_decoder->fb_dmabuffers[i]), 0);
        if (iret != BM_JPU_DEC_RETURN_CODE_OK) {
            goto error;
        }
    }

    ret = bm_jpu_dec_register_framebuffers(jpeg_decoder->decoder, jpeg_decoder->framebuffers, jpeg_decoder->num_framebuffers);
    if (ret != BM_JPU_DEC_RETURN_CODE_OK)
    {
        BM_JPU_ERROR("could not register framebuffers: %s. id=%lu", bm_jpu_dec_error_string(ret), get_cur_threadid());
        goto error;
    }

    return 1;

error:
    bm_jpu_jpeg_dec_deallocate_framebuffers(jpeg_decoder);
    return 0;
}


BmJpuDecReturnCodes bm_jpu_jpeg_dec_open(BmJpuJPEGDecoder **jpeg_decoder,
                                         BmJpuDecOpenParams *open_params,
                                         unsigned int num_extra_framebuffers)
{
    BmJpuDecReturnCodes ret = BM_JPU_DEC_RETURN_CODE_OK;
    BmJpuJPEGDecoder *jpegdec = NULL;
    bm_handle_t  handle = NULL;
    bm_status_t  bmlib_ret = BM_SUCCESS;

    if ((jpeg_decoder == NULL) || (open_params == NULL)) {
        BM_JPU_ERROR("bm_jpu_jpeg_dec_open params err: jpeg_decoder(0X%lx), open_params(0X%lx).", jpeg_decoder, open_params);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }

    jpegdec = BM_JPU_ALLOC(sizeof(BmJpuJPEGDecoder));
    if (jpegdec == NULL)
    {
        BM_JPU_ERROR("allocating memory for JPEG decoder object failed. id=%lu", get_cur_threadid());
        return BM_JPU_DEC_RETURN_CODE_ERROR;
    }

    memset(jpegdec, 0, sizeof(BmJpuJPEGDecoder));
    jpegdec->device_index = open_params->device_index;
    handle =  bm_jpu_get_handle(open_params->device_index);
    if (handle == 0) {
        BM_JPU_ERROR("bm_jpu_get_handle failed device_index:%d.\n", open_params->device_index);
        return BM_JPU_DEC_RETURN_CODE_ERROR;
    }
    jpegdec->num_extra_framebuffers = num_extra_framebuffers;

    size_t bs_size = 0;
    if (open_params->bs_buffer_size <= 0)
    {
        bm_jpu_dec_get_bitstream_buffer_info(&bs_size,
                                             &(jpegdec->bitstream_buffer_alignment));
    }
    else
    {
        int size = open_params->bs_buffer_size;
        size = (size+BS_MASK)&(~BS_MASK);

        bs_size = size;
        jpegdec->bitstream_buffer_alignment = 16;
    }
    jpegdec->device_index = open_params->device_index;
    if (jpegdec->bitstream_buffer != NULL) {
        BM_JPU_FREE(jpegdec->bitstream_buffer, sizeof(bm_device_mem_t));
        jpegdec->bitstream_buffer = NULL;
    }
    jpegdec->bitstream_buffer = BM_JPU_ALLOC(sizeof(bm_device_mem_t));
    bmlib_ret = bm_malloc_device_byte_heap_mask(handle, jpegdec->bitstream_buffer, HEAP_1_2, bs_size);
    if (bmlib_ret != BM_SUCCESS) {
        BM_JPU_ERROR("could not allocate DMA buffer for bitstream buffer with %u bytes and alignment %u. id=%lu",
                     bs_size,
                     jpegdec->bitstream_buffer_alignment,
                     get_cur_threadid());
        ret = BM_JPU_DEC_RETURN_ALLOC_MEM_ERROR;
        if (jpegdec->bitstream_buffer != NULL) {
            BM_JPU_FREE(jpegdec->bitstream_buffer, sizeof(bm_device_mem_t));
            jpegdec->bitstream_buffer = NULL;
        }
        goto error;
    }

    ret = bm_jpu_dec_open(&(jpegdec->decoder), open_params, jpegdec->bitstream_buffer, initial_info_callback, jpegdec);
    if (ret != BM_JPU_DEC_RETURN_CODE_OK) {
        if (jpegdec->bitstream_buffer != NULL) {
            bm_free_device(handle, *(jpegdec->bitstream_buffer));
            BM_JPU_FREE(jpegdec->bitstream_buffer, sizeof(bm_device_mem_t));
            jpegdec->bitstream_buffer = NULL;
        }
        goto error;
    }

    *jpeg_decoder = jpegdec;

    return BM_JPU_DEC_RETURN_CODE_OK;

error:
    if (jpegdec != NULL)
    {
        BM_JPU_FREE(jpegdec, sizeof(BmJpuJPEGDecoder));
    }

    return ret;
}


BmJpuDecReturnCodes bm_jpu_jpeg_dec_close(BmJpuJPEGDecoder *jpeg_decoder)
{
    bm_handle_t  handle = NULL;
    BmJpuDecReturnCodes ret = BM_JPU_DEC_RETURN_CODE_OK;

    if (jpeg_decoder == NULL) {
        BM_JPU_ERROR("bm_jpu_jpeg_dec_close params err: jpeg_decoder(0X%lx)", jpeg_decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }
    if (jpeg_decoder->decoder == NULL) {
        BM_JPU_ERROR("bm_jpu_jpeg_dec_open params err: jpeg_decoder->decoder(0X%lx).", jpeg_decoder->decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }

    bm_jpu_dec_close(jpeg_decoder->decoder);

    ret = bm_jpu_jpeg_dec_deallocate_framebuffers(jpeg_decoder);
    if (ret != BM_JPU_DEC_RETURN_CODE_OK){
        return ret;
    }

    handle =  bm_jpu_get_handle(jpeg_decoder->device_index);
    if (handle == 0) {
        BM_JPU_ERROR("bm_jpu_get_handle failed device_index:%d.\n", jpeg_decoder->device_index);
        return BM_JPU_DEC_RETURN_CODE_ERROR;
    }

    if (jpeg_decoder->bitstream_buffer != NULL) {
        bm_free_device(handle, *(jpeg_decoder->bitstream_buffer));
        BM_JPU_FREE(jpeg_decoder->bitstream_buffer, sizeof(bm_device_mem_t));
        jpeg_decoder->bitstream_buffer = NULL;
    }

    BM_JPU_FREE(jpeg_decoder, sizeof(BmJpuJPEGDecoder));

    return BM_JPU_DEC_RETURN_CODE_OK;
}


static BmJpuDecReturnCodes bm_jpu_jpeg_dec_deallocate_framebuffers(BmJpuJPEGDecoder *jpeg_decoder)
{
    if (jpeg_decoder == NULL) {
        BM_JPU_DEBUG("bm_jpu_jpeg_dec_deallocate_framebuffers params: jpeg_decoder(0X%lx)", jpeg_decoder);
        return BM_JPU_DEC_RETURN_CODE_OK;
    }

    if (jpeg_decoder->fb_dmabuffers == NULL) {
        BM_JPU_DEBUG("bm_jpu_jpeg_dec_deallocate_framebuffers params: jpeg_decoder->fb_dmabuffers(0X%lx).", jpeg_decoder->fb_dmabuffers);
        return BM_JPU_DEC_RETURN_CODE_OK;
    }

    unsigned int i;
    bm_handle_t handle = bm_jpu_get_handle(jpeg_decoder->device_index);

    for (i = 0; i < jpeg_decoder->num_framebuffers; ++i)
    {
        bm_free_device(handle, jpeg_decoder->fb_dmabuffers[i]);
    }

    if (jpeg_decoder->fb_dmabuffers != NULL) {
        BM_JPU_FREE(jpeg_decoder->fb_dmabuffers, sizeof(bm_device_mem_t*) * jpeg_decoder->num_framebuffers);
        jpeg_decoder->fb_dmabuffers = NULL;
    }

    if (jpeg_decoder->framebuffers != NULL) {
        BM_JPU_FREE(jpeg_decoder->framebuffers, sizeof(BmJpuFramebuffer) * jpeg_decoder->num_framebuffers);
        jpeg_decoder->framebuffers = NULL;
    }

    jpeg_decoder->num_framebuffers = 0;

    return BM_JPU_DEC_RETURN_CODE_OK;
}


int bm_jpu_jpeg_dec_can_decode(BmJpuJPEGDecoder *jpeg_decoder)
{
    return bm_jpu_dec_check_if_can_decode(jpeg_decoder->decoder);
}

BmJpuDecReturnCodes bm_jpu_jpeg_dec_decode(BmJpuJPEGDecoder *jpeg_decoder, uint8_t const *jpeg_data, size_t const jpeg_data_size)
{
    unsigned int output_code;
    BmJpuDecReturnCodes ret;
    BmJpuEncodedFrame encoded_frame;
    int count = 0;

    if ((jpeg_data == NULL) || (jpeg_data_size <= 0) || (jpeg_decoder == NULL)){
        BM_JPU_DEBUG("bm_jpu_jpeg_dec_decode params: jpeg_data(0X%lx), jpeg_data_size(%d), jpeg_decoder(0X%lx)", jpeg_data, jpeg_data_size, jpeg_decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }
    if (jpeg_decoder->decoder == NULL){
        BM_JPU_DEBUG("bm_jpu_jpeg_dec_decode params: jpeg_decoder->decoder(0X%lx)", jpeg_decoder->decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }

    memset(&encoded_frame, 0, sizeof(encoded_frame));
    encoded_frame.data = (uint8_t *)jpeg_data;
    encoded_frame.data_size = jpeg_data_size;

    do{
        ret = bm_jpu_dec_decode(jpeg_decoder->decoder, &encoded_frame, &output_code);
    }while( ret == BM_JPU_DEC_RETURN_CODE_TIMEOUT  && (count++ < 3) );

    if (ret != BM_JPU_DEC_RETURN_CODE_OK) {
        bm_jpu_jpeg_dec_deallocate_framebuffers(jpeg_decoder);
        return ret;
    }
    if (output_code & BM_JPU_DEC_OUTPUT_CODE_DECODED_FRAME_AVAILABLE)
    {
        ret = bm_jpu_dec_get_decoded_frame(jpeg_decoder->decoder, &(jpeg_decoder->raw_frame));
        if (ret != BM_JPU_DEC_RETURN_CODE_OK) {
            bm_jpu_jpeg_dec_deallocate_framebuffers(jpeg_decoder);
            return ret;
        }
    }
    else
    {
        jpeg_decoder->raw_frame.framebuffer = NULL;
    }

    return BM_JPU_DEC_RETURN_CODE_OK;
}

void bm_jpu_jpeg_dec_get_info(BmJpuJPEGDecoder *jpeg_decoder, BmJpuJPEGDecInfo *info)
{
    if ((jpeg_decoder == NULL) || (info == NULL)){
        BM_JPU_ERROR("bm_jpu_jpeg_dec_get_info params err: jpeg_decoder(0X%lx), info(%d).", jpeg_decoder, info);
        return;
    }
    if (jpeg_decoder->framebuffers == NULL){
        BM_JPU_ERROR("bm_jpu_jpeg_dec_get_info params err: jpeg_decoder->framebuffers(0X%lx)", jpeg_decoder->framebuffers);
        return;
    }

    info->aligned_frame_width  = jpeg_decoder->calculated_sizes.aligned_frame_width;
    info->aligned_frame_height = jpeg_decoder->calculated_sizes.aligned_frame_height;

    info->actual_frame_width  = jpeg_decoder->initial_info.frame_width;
    info->actual_frame_height = jpeg_decoder->initial_info.frame_height;

    info->y_stride    = jpeg_decoder->calculated_sizes.y_stride;
    info->cbcr_stride = jpeg_decoder->calculated_sizes.cbcr_stride;

    info->y_size    = jpeg_decoder->calculated_sizes.y_size;
    info->cbcr_size = jpeg_decoder->calculated_sizes.cbcr_size;

    info->y_offset  = jpeg_decoder->framebuffers[0].y_offset;
    info->cb_offset = jpeg_decoder->framebuffers[0].cb_offset;
    info->cr_offset = jpeg_decoder->framebuffers[0].cr_offset;

    info->framebuffer = jpeg_decoder->raw_frame.framebuffer;

    info->color_format = jpeg_decoder->initial_info.color_format;

    info->chroma_interleave = jpeg_decoder->calculated_sizes.chroma_interleave;
}


BmJpuDecReturnCodes bm_jpu_jpeg_dec_frame_finished(BmJpuJPEGDecoder *jpeg_decoder, BmJpuFramebuffer *framebuffer)
{
    if ((framebuffer == NULL) || (jpeg_decoder == NULL)){
        BM_JPU_ERROR("bm_jpu_jpeg_dec_frame_finished params err: framebuffer(0X%lx), jpeg_decoder(0X%lx).", framebuffer, jpeg_decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }
    if (jpeg_decoder->decoder == NULL){
        BM_JPU_ERROR("bm_jpu_jpeg_dec_frame_finished params err: jpeg_decoder->decoder(0X%lx)", jpeg_decoder->decoder);
        return BM_JPU_DEC_RETURN_CODE_INVALID_PARAMS;
    }

    return bm_jpu_dec_mark_framebuffer_as_displayed(jpeg_decoder->decoder, framebuffer);
}

BmJpuDecReturnCodes bm_jpu_jpeg_dec_flush(BmJpuJPEGDecoder *jpeg_decoder)
{
    if (jpeg_decoder && jpeg_decoder->decoder)
        return bm_jpu_dec_flush(jpeg_decoder->decoder);

    return BM_JPU_DEC_RETURN_CODE_OK; // TODO
}



/******************
 ** JPEG ENCODER **
 ******************/


struct _BmJpuJPEGEncoder
{
    BmJpuEncoder *encoder;

    bm_device_mem_t *bitstream_buffer;

    size_t bitstream_buffer_size;
    unsigned int bitstream_buffer_alignment;

    BmJpuEncInitialInfo initial_info;

    unsigned int frame_width, frame_height;

    BmJpuFramebufferSizes calculated_sizes;

    unsigned int quality_factor;

    BmJpuColorFormat color_format;
    int packed_format;
    int chroma_interleave;
    int device_index;

    int rotationEnable;
    int mirrorEnable;
    int mirrorDirection;
    int rotationAngle;
};


static BmJpuEncReturnCodes bm_jpu_jpeg_enc_open_internal(BmJpuJPEGEncoder *jpeg_encoder);
static BmJpuEncReturnCodes bm_jpu_jpeg_enc_close_internal(BmJpuJPEGEncoder *jpeg_encoder);


static BmJpuEncReturnCodes bm_jpu_jpeg_enc_open_internal(BmJpuJPEGEncoder *jpeg_encoder)
{
    BmJpuEncOpenParams open_params;
    BmJpuEncReturnCodes ret = BM_JPU_ENC_RETURN_CODE_OK;

    if(!(jpeg_encoder != NULL)) {
        BM_JPU_ERROR("bm_jpu_jpeg_enc_open_internal params err: jpeg_encoder(0X%lx).", jpeg_encoder);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }
    if(!(jpeg_encoder->frame_width > 0) ||
       !(jpeg_encoder->frame_height > 0) ||
       !(jpeg_encoder->encoder == NULL)) {
        BM_JPU_ERROR("bm_jpu_jpeg_enc_open_internal params err: jpeg_encoder->encoder(0X%lx), jpeg_encoder->frame_width(%d), jpeg_encoder->frame_height(%d)", jpeg_encoder->encoder, jpeg_encoder->frame_width, jpeg_encoder->frame_height);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }

    ret = bm_jpu_enc_set_default_open_params(&open_params);
    if (ret != BM_JPU_ENC_RETURN_CODE_OK) {
        return ret;
    }

    open_params.frame_width  = jpeg_encoder->frame_width;
    open_params.frame_height = jpeg_encoder->frame_height;
    open_params.color_format = jpeg_encoder->color_format;
    open_params.quality_factor = jpeg_encoder->quality_factor;
    open_params.packed_format  = jpeg_encoder->packed_format;
    open_params.chroma_interleave = jpeg_encoder->chroma_interleave;
    open_params.device_index = jpeg_encoder->device_index;

    open_params.rotationEnable  = jpeg_encoder->rotationEnable;
    open_params.rotationAngle   = jpeg_encoder->rotationAngle;
    open_params.mirrorEnable    = jpeg_encoder->mirrorEnable;
    open_params.mirrorDirection = jpeg_encoder->mirrorDirection;

    ret = bm_jpu_enc_open(&(jpeg_encoder->encoder), &open_params, jpeg_encoder->bitstream_buffer);
    if (ret != BM_JPU_ENC_RETURN_CODE_OK)
        goto error;

    ret = bm_jpu_enc_get_initial_info(jpeg_encoder->encoder, &(jpeg_encoder->initial_info));
    if (ret != BM_JPU_ENC_RETURN_CODE_OK)
        goto error;

    ret = bm_jpu_calc_framebuffer_sizes(jpeg_encoder->color_format,
                                  jpeg_encoder->frame_width,
                                  jpeg_encoder->frame_height,
                                  jpeg_encoder->initial_info.framebuffer_alignment,
                                  0, // TODO chroma_interleave
                                  &(jpeg_encoder->calculated_sizes));

    return ret;

error:
    bm_jpu_jpeg_enc_close_internal(jpeg_encoder);

    return ret;
}


static BmJpuEncReturnCodes bm_jpu_jpeg_enc_close_internal(BmJpuJPEGEncoder *jpeg_encoder)
{
    if (jpeg_encoder == NULL){
        BM_JPU_ERROR("bm_jpu_jpeg_enc_close_internal params err: jpeg_encoder(0X%lx).", jpeg_encoder);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }

    if (jpeg_encoder->encoder != NULL)
    {
        bm_jpu_enc_close(jpeg_encoder->encoder);
        jpeg_encoder->encoder = NULL;
    }

    return BM_JPU_ENC_RETURN_CODE_OK;
}
#if !defined(_WIN32)
int bm_jpu_jpeg_get_dump()
{
    int ret = bm_jpu_get_dump();
    return ret;
}
#endif
BmJpuEncReturnCodes bm_jpu_jpeg_enc_open(BmJpuJPEGEncoder **jpeg_encoder,
                                         int bs_buffer_size,
                                         int device_index)
{
    BmJpuJPEGEncoder *jpegenc = NULL;
    bm_status_t  ret = BM_SUCCESS;

    if (jpeg_encoder == NULL){
        BM_JPU_ERROR("bm_jpu_jpeg_enc_open params err: jpeg_encoder(0X%lx).", jpeg_encoder);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }

    jpegenc = BM_JPU_ALLOC(sizeof(BmJpuJPEGEncoder));
    if (jpegenc == NULL)
    {
        BM_JPU_ERROR("allocating memory for JPEG encoder object failed. id=%lu", get_cur_threadid());
        return BM_JPU_ENC_RETURN_CODE_ERROR;
    }

    memset(jpegenc, 0, sizeof(BmJpuJPEGEncoder));
    jpegenc->device_index = device_index;

    if (bs_buffer_size <= 0)
    {
        bm_jpu_enc_get_bitstream_buffer_info(&(jpegenc->bitstream_buffer_size),
                                             &(jpegenc->bitstream_buffer_alignment));
    }
    else
    {
        bs_buffer_size = (bs_buffer_size+BS_MASK)&(~BS_MASK);

        jpegenc->bitstream_buffer_size = bs_buffer_size;
        jpegenc->bitstream_buffer_alignment = 16;
    }

    if (jpegenc->bitstream_buffer != NULL) {
        BM_JPU_FREE(jpegenc->bitstream_buffer, sizeof(bm_device_mem_t));
    }
    jpegenc->bitstream_buffer = BM_JPU_ALLOC(sizeof(bm_device_mem_t));
    bm_handle_t handle = bm_jpu_get_handle(jpegenc->device_index);
    ret = bm_malloc_device_byte_heap_mask(handle, jpegenc->bitstream_buffer, HEAP_1_2, jpegenc->bitstream_buffer_size);

    if (ret != BM_SUCCESS)
    {
        BM_JPU_ERROR("could not allocate DMA buffer for bitstream buffer with %u bytes and alignment %u. id=%lu",
                     jpegenc->bitstream_buffer_size,
                     jpegenc->bitstream_buffer_alignment,
                     get_cur_threadid());
        if (jpegenc->bitstream_buffer != NULL) {
            BM_JPU_FREE(jpegenc->bitstream_buffer, sizeof(bm_device_mem_t));
            jpegenc->bitstream_buffer = NULL;
        }
        return BM_JPU_DEC_RETURN_ALLOC_MEM_ERROR;
    }


    /* bm_jpu_enc_open() is called later on demand during encoding, to accomodate
     * for potentially changing parameters like width, height, quality factor */

    *jpeg_encoder = jpegenc;

    return BM_JPU_ENC_RETURN_CODE_OK;
}


BmJpuEncReturnCodes bm_jpu_jpeg_enc_close(BmJpuJPEGEncoder *jpeg_encoder)
{
    if (jpeg_encoder == NULL){
        BM_JPU_ERROR("bm_jpu_jpeg_enc_close params err: jpeg_encoder(0X%lx).", jpeg_encoder);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }

    bm_jpu_jpeg_enc_close_internal(jpeg_encoder);

    bm_handle_t handle = bm_jpu_get_handle(jpeg_encoder->device_index);
    if (jpeg_encoder->bitstream_buffer != NULL) {
        bm_free_device(handle, *(jpeg_encoder->bitstream_buffer));
        BM_JPU_FREE(jpeg_encoder->bitstream_buffer, sizeof(bm_device_mem_t));
        jpeg_encoder->bitstream_buffer = NULL;
    }

    BM_JPU_FREE(jpeg_encoder, sizeof(BmJpuJPEGEncoder));

    return BM_JPU_ENC_RETURN_CODE_OK;
}

BmJpuEncReturnCodes bm_jpu_jpeg_enc_encode(BmJpuJPEGEncoder *jpeg_encoder,
                                           BmJpuFramebuffer const *framebuffer,
                                           BmJpuJPEGEncParams const *params,
                                           void **acquired_handle,
                                           size_t *output_buffer_size)
{
    unsigned int output_code;
    BmJpuEncParams enc_params;
    BmJpuEncReturnCodes ret;
    BmJpuRawFrame raw_frame;
    BmJpuEncodedFrame encoded_frame;
    int count = 0;

    if ((jpeg_encoder == NULL) || (framebuffer == NULL) || (params == NULL)){
        BM_JPU_ERROR("bm_jpu_jpeg_enc_encode params err: jpeg_encoder(0X%lx), framebuffer(0X%lx), params(0X%lx).", jpeg_encoder, framebuffer, params);
        return BM_JPU_ENC_RETURN_CODE_INVALID_PARAMS;
    }

    if (acquired_handle != NULL)
        *acquired_handle = NULL;

    BM_JPU_DEBUG("jpeg_encoder->device_index   = %d", jpeg_encoder->device_index);
    BM_JPU_DEBUG("jpeg_encoder->encoder        = %p", (void*)(jpeg_encoder->encoder));
    BM_JPU_DEBUG("jpeg_encoder->frame_width    = %d", jpeg_encoder->frame_width);
    BM_JPU_DEBUG("jpeg_encoder->frame_height   = %d", jpeg_encoder->frame_height);
    BM_JPU_DEBUG("jpeg_encoder->quality_factor = %d", jpeg_encoder->quality_factor);
    BM_JPU_DEBUG("jpeg_encoder->color_format   = %d", jpeg_encoder->color_format);

    BM_JPU_DEBUG("params->frame_width    = %d", params->frame_width);
    BM_JPU_DEBUG("params->frame_height   = %d", params->frame_height);
    BM_JPU_DEBUG("params->quality_factor = %d", params->quality_factor);
    BM_JPU_DEBUG("params->color_format   = %d", params->color_format);

    if ((jpeg_encoder->encoder == NULL) ||
        (jpeg_encoder->frame_width    != params->frame_width) ||
        (jpeg_encoder->frame_height   != params->frame_height) ||
        (jpeg_encoder->quality_factor != params->quality_factor) ||
        (jpeg_encoder->color_format   != params->color_format))
    {
        bm_jpu_jpeg_enc_close_internal(jpeg_encoder);

        jpeg_encoder->frame_width    = params->frame_width;
        jpeg_encoder->frame_height   = params->frame_height;
        jpeg_encoder->quality_factor = params->quality_factor;
        jpeg_encoder->color_format   = params->color_format;
        jpeg_encoder->packed_format   = params->packed_format;
        jpeg_encoder->chroma_interleave = params->chroma_interleave;
        jpeg_encoder->rotationEnable = params->rotationEnable;
        jpeg_encoder->rotationAngle  = params->rotationAngle;
        jpeg_encoder->mirrorEnable   = params->mirrorEnable;
        jpeg_encoder->mirrorDirection= params->mirrorDirection;

        ret = bm_jpu_jpeg_enc_open_internal(jpeg_encoder);
        if (ret != BM_JPU_ENC_RETURN_CODE_OK)
            return ret;
    }

    memset(&enc_params, 0, sizeof(enc_params));
    enc_params.acquire_output_buffer = params->acquire_output_buffer;
    enc_params.finish_output_buffer  = params->finish_output_buffer;
    enc_params.write_output_data     = params->write_output_data;
    enc_params.output_buffer_context = params->output_buffer_context;

    memset(&raw_frame, 0, sizeof(raw_frame));
    raw_frame.framebuffer = (BmJpuFramebuffer *)framebuffer;

    memset(&encoded_frame, 0, sizeof(encoded_frame));

    do{
        ret = bm_jpu_enc_encode(jpeg_encoder->encoder, &raw_frame, &encoded_frame, &enc_params, &output_code);
    }while( ret == BM_JPU_ENC_RETURN_CODE_TIMEOUT  && (count++ < 3) );

    if (acquired_handle != NULL)
        *acquired_handle = encoded_frame.acquired_handle;
    if (output_buffer_size != NULL)
        *output_buffer_size = encoded_frame.data_size;

    return ret;
}
