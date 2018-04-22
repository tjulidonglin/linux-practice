;;kernel.asm
bits 32
section .text
align 4
dd 0x1BADB002 ;magic
dd 0x00 ;flags
dd -(0x1BADB002 + 0x00) ;checksum

global start
extern kmain  ;defined in kernel.c file

start:
	cli ;close external interrupt
    call kmain
    hlt  ;halt cpu

