#!/bin/bash
#sh ./00-install.sh
basedir=$(pwd)

cd ../libvirt/
git clean -fdx && git reset --hard
git pull
git checkout v3.2-maint
if [ $? != 0 ]
then
	echo "Switch Libvirt-3.2 branch failed!"
	exit 1
fi
##tar -xzf ${basedir}/gnulib.tar.gz -C ./
sed -i '1047a#include <sys/uio.h>' src/util/virlog.c
export GNULIB_SRCDIR=/root/code/gnulib
./autogen.sh --prefix=/usr --libdir=/usr/lib64 --sysconfdir=/etc --libexecdir=/usr/libexec --localstatedir=/var --bindir=/usr/bin --sbindir=/usr/sbin --datadir=/usr/share --includedir=/usr/include --mandir=/usr/share/man --with-qemu --without-xen --without-openvz --without-lxc --without-sasl  --with-polkit --without-uml --without-phyp --without-hyperv --without-vmware --without-xenapi --without-vz --without-bhyve --with-qemu
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

autoreconf -f -i
chmod a+x configure
chmod a+x build-aux/vc-list-files
chmod a+x build-aux/useless-if-before-free
touch docs/apibuild.py
touch src/remote/remote_protocol.x
touch src/remote/uvp_protocol.x
touch src/remote/qemu_protocol.x
touch src/logging/log_protocol.x
./configure --build=x86_64-Huawei-linux-gnu --host=x86_64-Huawei-linux-gnu --program-prefix= --disable-dependency-tracking --prefix=/usr --exec-prefix=/usr --bindir=/usr/bin --sbindir=/usr/sbin --sysconfdir=/etc --datadir=/usr/share --includedir=/usr/include --libdir=/usr/lib64 --libexecdir=/usr/libexec --localstatedir=/var --sharedstatedir=/var/lib --mandir=/usr/share/man --infodir=/usr/share/info --without-xen --with-qemu --without-openvz --without-lxc --without-vbox --without-libxl --with-sasl --with-avahi --with-polkit --with-libvirtd --without-uml --without-phyp --with-esx --without-hyperv --without-vmware --without-xenapi --without-vz --without-bhyve --with-interface --with-network --with-storage-fs --with-storage-lvm --with-storage-iscsi --with-storage-scsi --with-storage-disk --with-storage-mpath --with-storage-rbd --without-storage-sheepdog --with-storage-gluster --without-storage-zfs --without-storage-vstorage --with-numactl --without-numad --with-hirmd --with-nettle --with-uvpkmc --without-capng --with-fuse --with-netcf --with-selinux --with-selinux-mount=/sys/fs/selinux --without-apparmor --without-hal --with-udev --with-yajl --without-sanlock --without-libpcap --without-macvtap --with-audit --with-dtrace --with-driver-modules --with-firewalld --without-wireshark-dissector --without-pm-utils --without-nss-plugin --with-packager-version=1 --with-qemu-user=qemu --with-qemu-group=qemu --with-tls-priority=NORMAL --enable-werror --enable-expensive-tests --with-init-script=systemd --enable-debug
