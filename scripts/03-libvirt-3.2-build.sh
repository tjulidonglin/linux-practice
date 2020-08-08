#!/bin/bash
sh ./00-install.sh

cd ../libvirt/
git clean -fdx && git reset --hard
git pull
git checkout maint-3.2
if [ $? != 0 ]
then
	echo "Switch Libvirt-3.2 branch failed!"
	exit 1
fi

./autobuild.sh
 ./configure --prefix=/usr --libdir=/usr/lib64 --sysconfdir=/etc --libexecdir=/usr/libexec --localstatedir=/var --bindir=/usr/bin --sbindir=/usr/sbin --datadir=/usr/share --includedir=/usr/include --mandir=/usr/share/man --with-qemu --without-xen --without-openvz --without-lxc --without-sasl  --with-polkit --without-uml --without-phyp --without-hyperv --without-vmware --without-xenapi --without-vz --without-bhyve --with-qemu
if [ $? != 0 ]
then
	echo "Configure Libvirt-3.2 failed!"
	exit 2
fi

make -j12
if [ $? != 0 ]
then
	echo "Make Libvirt-3.2 failed!"
	exit 3
fi

make install
if [ $? != 0 ]
then
	echo "Install Libvirt-3.2 failed!"
	exit 4
fi

cd -
echo "Build Libvirt-3.2 success"
exit 0

