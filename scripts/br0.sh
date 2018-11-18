#!/bin/bash

ovs-vsctl add-br br0
ovs-vsctl add-port br0 eth0
ifconfig eth0 0
dhclient br0
echo "Setup ovs bridge successfully"
