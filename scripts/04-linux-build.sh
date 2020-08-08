#!/bin/bash
sh ./00-install.sh
cd ../linux-stable/
git clean -fdx && git reset --hard
#git pull
git checkout linux-5.4.y
if [ $? != 0 ]
then
	echo "Switch linux branch failed!"
	exit 1
fi
cp /boot/config-5.4.0-42-generic ./.config

make -j12 && make modules -j12
if [ $? != 0 ]
then
	echo "Make linux failed!"
	exit 3
fi

make modules_install && make install
if [ $? != 0 ]
then
	echo "Install linux failed!"
	exit 4
fi

cd -
echo "Build linux success"
exit 0
