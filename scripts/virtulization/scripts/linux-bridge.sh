#!/bin/bash

if [ -f /usr/sbin/brctl ]
then
    brctl addbr br0
    brctl addif br0 eth0
    brctl stp br0 on
    ifconfig eth0 0
    dhclient br0
    echo "Success"
else
	echo "Install bridge-utils first."
	apt install -y bridge-utils
    brctl addbr br0
    brctl addif br0 eth0
    brctl stp br0 on
    ifconfig eth0 0
    dhclient br0
    echo "Success"
fi

