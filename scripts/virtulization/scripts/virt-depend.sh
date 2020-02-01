#!/bin/bash
fn_qemu_dependence()
{
    apt update 
    apt install  -y pkgconf zlib1g-dev libsdl2-dev libglib2.0-dev libpixman-1-dev texinfo libusb-1.0-0-dev g++ libspice-server-dev
}

fn_linux_dependence()
{
    apt update 
    apt install -y dot2tex dvipng librsvg2-bin python3-sphinx
}

fn_libvirt_dependence()
{
    apt update 
    apt install -y libtool autoconf autopoint libxml2-utils xsltproc libxml2-dev libpciaccess-dev libyajl-dev 
}

fn_config_qemu()
{
    ./configure --enable-kvm --enable-vnc --enable-debug --enable-sdl --enable-docs --enable-libusb --disable-xen --disable-spice --target-list=x86_64-softmmu
}

fn_systemenv_dependence()
{
	apt update
	apt install -y tree exuberant-ctags
}

fn_systemenv_dependence
fn_libvirt_dependence
fn_linux_dependence
