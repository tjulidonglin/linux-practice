#!/bin/bash

apt update
echo "Begin to install dependent packages of libvirt"
apt install -y libtool autoconf autopoint libxml2-utils xsltproc libxml2-dev libpciaccess-dev libyajl-dev autopoint
echo "Finish installing dependent packages"

