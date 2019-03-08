#!/bin/bash

brctl addbr br0
brctl addif br0 eth0
brctl stp br0 on
ifconfig eth0 0
dhclient br0
echo "Success"
