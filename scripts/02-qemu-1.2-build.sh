#!/bin/bash
sh ./00-install.sh
cd ../qemu/
git clean -fdx && git reset --hard
git pull
git checkout stable-1.2
if [ $? != 0 ]
then
	echo "Switch Qemu-1.2 branch failed!"
	exit 1
fi
./configure --enable-kvm --enable-vnc --enable-debug --target-list=x86_64-softmmu \
--prefix=/usr --disable-seccomp --disable-virtfs --disable-sdl --disable-docs \
--disable-spice --disable-guest-agent --disable-usb-redir --disable-smartcard-nss \
--disable-smartcard --disable-libiscsi --enable-vhost-net --disable-attr --disable-cap-ng \
--disable-linux-aio --disable-vde --disable-bsd-user --disable-linux-user --enable-user \
--disable-slirp --disable-xen

if [ $? != 0 ]
then
	echo "Configure Qemu-1.2 failed!"
	exit 2
fi

make -j12
if [ $? != 0 ]
then
	echo "Make Qemu-1.2 failed!"
	exit 3
fi

make install
if [ $? != 0 ]
then
	echo "Install Qemu-1.2 failed!"
	exit 4
fi

cd -
echo "Build Qemu-1.2 success"
exit 0
