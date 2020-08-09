#!/bin/bash
yum install -y gcc git wget vim cscope ctags
#yum install -y openssh-server gcc g++ make autopoint pkgconf zlib1g-dev libsdl2-dev libglib2.0-dev libpixman-1-dev texinfo libusb-1.0-0-dev libspice-server-dev libncurses5-dev libtool autoconf libxml2-utils xsltproc libxml2-dev libpciaccess-dev libyajl-dev tree python3-pip libnl-3-dev libnl-route-3-dev libdevmapper-dev openvswitch-switch net-tools git vim samba openssh-server pkg-config gnutls-bin openvswitch-switch 
yum install -y zlib-devel SDL-devel glib2-devel pixman-devel spice-server spice-server-devel libcap-devel libattr-devel ncurses-devel bc

#centos/redhat系统支持kernel开发的依赖包
yum install kernel kernel-headers kernel-devel kernel-tools kernel-tools-libs -y

#yum工具
yum install yum-utils

