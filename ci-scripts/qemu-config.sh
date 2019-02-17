#!/bin/bash

apt update
echo "Begin to install dependent packages of qemu"
apt install -y pkgconf zlib1g-dev libsdl2-dev libglib2.0-dev libpixman-1-dev texinfo libusb-1.0-0-dev g++ libspice-server-dev
apt install -y libncurses5-dev #for seabios 
echo "Finish installing dependent packages"

