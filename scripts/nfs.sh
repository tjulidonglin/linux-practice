#!/bin/bash

echo "/mnt/sdb/lidonglin/kvm/ *(rw,sync,no_root_squash,no_subtree_check,insecure)" > /etc/exports
exportfs -r
systemctl restart rpcbind
systemctl restart nfs
showmount -e
