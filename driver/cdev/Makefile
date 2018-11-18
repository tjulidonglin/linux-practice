KVERS=$(shell uname -r)
obj-m += cdev.o
build:kernel_modules
#EXTRA_CFLAGS=-g -O0
kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules
clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
