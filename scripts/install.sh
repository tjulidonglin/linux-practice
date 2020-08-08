#!/bin/bash

# compile qemu
apt install -y gdb gcc g++ make autopoint pkgconf zlib1g-dev libsdl2-dev libglib2.0-dev libpixman-1-dev texinfo libusb-1.0-0-dev libspice-server-dev

# compile seabios
apt install -y libncurses5-dev

# compile libvirt
apt install -y libtool autoconf libxml2-utils xsltproc libxml2-dev libpciaccess-dev libyajl-dev python3-pip libnl-3-dev libnl-route-3-dev libdevmapper-dev

# compile linux
apt install -y libssl-dev dot2tex dvipng librsvg2-bin python3-sphinx libncurses5-dev

# install ovs
apt install -y openvswitch-switch

# system utils
apt install -y git vim samba openssh-server pkg-config gnutls-bin tree

# ifconfig
apt install -y net-tools

# cscope
apt install -y exuberant-ctags cscope

# support exfat to access SSD
apt install -y exfat-utils

# performence tools
apt install -y htop hwloc numactl stress sysbench lmbench sysstat
