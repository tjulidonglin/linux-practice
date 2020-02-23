#!/bin/bash
ip link set dev tap0 master br0
ip link set dev tap0 up
exit 0
