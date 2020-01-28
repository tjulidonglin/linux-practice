obj-m += proc.o

KVERS := $(shell uname -r)


all:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules
	@gcc main.c -o test

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
	@rm -rf test
