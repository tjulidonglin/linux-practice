#!/bin/bash

# compile qemu
apt install -y gcc g++ make autopoint pkgconf zlib1g-dev libsdl2-dev libglib2.0-dev libpixman-1-dev texinfo libusb-1.0-0-dev libspice-server-dev

# compile libvirt
apt install -y libncurses5-dev libtool autoconf libxml2-utils xsltproc libxml2-dev libpciaccess-dev libyajl-dev python3-pip libnl-3-dev libnl-route-3-dev libdevmapper-dev

# install ovs
apt install -y openvswitch-switch

# system utils
apt install -y git vim samba openssh-server pkg-config gnutls-bin tree

# ifconfig
apt install -y net-tools
