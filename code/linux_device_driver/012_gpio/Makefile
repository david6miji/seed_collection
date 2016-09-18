#
# kernel 3.0 driver Makefile
#
obj-m  			:= drv_gpio.o
drv_gpio-objs 	= gpio_main.o

CROSS_PATH		= /opt/gcc-linaro-arm-linux-gnueabihf-4.9-2014.09_linux/
CROSS_PREFIX	= arm-linux-gnueabihf-
KDIR   			:= /work/kernel/build
PWD    			:= $(shell pwd)

default:
	ARCH=arm $(MAKE) arm=ARM CROSS_COMPILE=${CROSS_PATH}/bin/${CROSS_PREFIX} -C $(KDIR) M=$(PWD)  
	scp drv_gpio.ko root@192.168.1.206:/root/

clean :
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf .tmp_versions
	rm -rf modules.order
	rm -rf Module.symvers
	