ifneq ($(KERNELRELEASE),)
obj-m := gpio.o
else
KDIR :=/home/fang/raspberrypi/linux-4.8
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
endif

