# Comment/uncomment the	following line to disable/enable debugging
#DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  DEBFLAGS = -O	-g # "-O" is needed to expand inlines
else
  DEBFLAGS = -O2
endif

export CC="$(CROSS_COMPILE)gcc"
export AR="$(CROSS_COMPILE)ar"
export CXX="${CROSS_COMPILE}g++"
export AS="${CROSS_COMPILE}as"
export LD="${CROSS_COMPILE}ld"
export RANLIB="${CROSS_COMPILE}ranlib"
export READELF="${CROSS_COMPILE}readelf"
export STRIP="${CROSS_COMPILE}strip"

//EXTRA_CFLAGS +=	$(DEBFLAGS) -I$(LDDINCDIR)
LDDINCDIR = -I$(BMVID_TOP_DIR)/video/driver
EXTRA_CFLAGS +=	$(DEBFLAGS) $(LDDINCDIR)  -DCNM_FPGA_PLATFORM -DCNM_FPGA_PCI_INTERFACE -DCONFIG_PM

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= vpu.o

else

//KERNELDIR := ../../../../../kernel
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD	  := $(shell pwd)

default:
	$(MAKE)	-C $(KERNELDIR)	M=$(PWD) modules

endif



clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

depend .depend dep:
	$(CC) $(CFLAGS)	-M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include	.depend
endif
