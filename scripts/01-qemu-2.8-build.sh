#!/bin/bash
sh ./00-install.sh
cd ../qemu/
git clean -fdx && git reset --hard
git pull
git checkout stable-2.8
if [ $? != 0 ]
then
	echo "Switch Qemu-2.8 branch failed!"
	exit 1
fi
./configure --prefix=/usr --libdir=/usr/lib64 --sysconfdir=/etc --interp-prefix=/usr/qemu-%M --libexecdir=/usr/libexec --with-confsuffix=/qemu-kvm --target-list=x86_64-softmmu --localstatedir=/var '--extra-ldflags=-Wl,--build-id -Wl,-z,relro -Wl,-z,now -Wl,--disable-new-dtags,--rpath,/usr/lib64:/usr/lib -Wl,-z,noexecstack' '--extra-cflags=-O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -DPIE -fno-inline -fPIC -fvisibility=hidden -fstack-check' --disable-rdma --enable-kvm --enable-numa --disable-sdl --disable-spice --disable-smartcard --enable-linux-aio
if [ $? != 0 ]
then
	echo "Configure Qemu-2.8 failed!"
	exit 2
fi
sed -i '40s/static//g' ../qemu/util/memfd.c
make -j12
if [ $? != 0 ]
then
	echo "Make Qemu-2.8 failed!"
	exit 3
fi

make install
if [ $? != 0 ]
then
	echo "Install Qemu-2.8 failed!"
	exit 4
fi

cd -
echo "Build Qemu-2.8 success"
exit 0
