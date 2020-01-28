obj-m += seq_file.o

KVERS := $(shell uname -r)


all:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules
	@gcc main.c -o main

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
	@rm -rf main
