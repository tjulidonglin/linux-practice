obj-m += traverse.o

KVERS := $(shell uname -r)


all:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
