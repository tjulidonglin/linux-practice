#!/bin/bash
#Function: pull Git repos

for dir in `ls`
do
    if [ -d $dir ]
    then
        cd ${dir} >/dev/null 2>&1
		git pull > /dev/null 2>&1
		cd - >/dev/null 2>&1
        echo "Finish to update ${dir}"
    fi
done
