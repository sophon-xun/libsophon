#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "vppion.h"
#include "vpplib.h"

int main(int argc, char *argv[])
{
    vpp_mat src;
    vpp_mat dst;
    char * ch_b_name;
    char * ch_g_name;
    char * ch_r_name;
    char *input_name;
    int width, height;

    if (argc != 7)
    {
        printf("usage: %d\n", argc);
        printf("%s width height in_bgr24.bin ch_b_name ch_g_name ch_r_name\n", argv[0]);
        printf("example:\n");
        printf("        %s 1920 1080 bgr-org-opencv.bin b.bmp g.bmp r.bmp\n", argv[0]);
        return 0;
    }

    width = atoi(argv[1]);
    height = atoi(argv[2]);

    input_name = argv[3];
    ch_b_name = argv[4];
    ch_g_name = argv[5];
    ch_r_name = argv[6];

    if (vpp_creat_ion_mem(&src, FMT_BGR, width, height) == VPP_ERR) {
        goto err0;
    }
    if (vpp_creat_ion_mem(&dst, FMT_RGBP_C, width, height) == VPP_ERR) {
        goto err1;
    }

    src.is_pa = 0;
    dst.is_pa = 0;

    if (vpp_read_file(&src, NULL, input_name) < 0)
    {
        printf("vpp_read_file failed, src\n");
        goto err2;
    }

    ion_invalidate(NULL, dst.va[0], dst.ion_len[0]);

    vpp_split_to_bgr(&src, &dst);

    unsigned char * pix_0 = dst.va[0];
    unsigned char * pix_1 = pix_0 + src.rows * ALIGN(src.cols , STRIDE_ALIGN);
    unsigned char * pix_2 = pix_1 + src.rows * ALIGN(src.cols , STRIDE_ALIGN);

    vpp_bmp_gray(ch_b_name, (unsigned  char *)pix_0, dst.cols, dst.rows,dst.stride);
    vpp_bmp_gray(ch_g_name, (unsigned  char *)pix_1, dst.cols, dst.rows,dst.stride);
    vpp_bmp_gray(ch_r_name, (unsigned  char *)pix_2, dst.cols, dst.rows,dst.stride);

err2:
    vpp_free_ion_mem(&dst);
err1:
    vpp_free_ion_mem(&src);
err0:  
    return 0;
}
