#!/bin/bash
#function: start win7

/root/code/qemu-upstream/x86_64-softmmu/qemu-system-x86_64 -smp 4 -m 4096 -enable-kvm -vnc :0 -hda /root/win7_64.vhd  -hdb /root/Images/win7_data.vhd -usbdevice tablet -device usb-ehci -net nic,model=virtio -net tap,ifname=tap0,script=/etc/qemu-ifup,downscript=no --daemonize -device nec-usb-xhci -usbdevice host:0fe6:9700 
