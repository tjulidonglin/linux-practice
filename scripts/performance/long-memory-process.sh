#!/bin/bash
ps -eo pid,user,ppid,%mem,%cpu,cmd --sort=-%cpu | head | tail -n +2 | awk '{print $1}' > ./long-running-processes.txt

echo "------------------------------------------------"
echo "Uname     PID   CMD      Process_Running_Time"
echo "------------------------------------------------"

for pid in `cat ./long-running-processes.txt`
do
	username=$(ps -u -p $pid | tail -1 | awk '{print $1}')
	pruntime=$(ps -p $pid -o etime | tail -1)
	ocmd=$(ps -p $pid | tail -1 | awk '{print $4}')
	echo "$username $pid $ocmd $pruntime"
done | column -t
echo "------------------------------------------------"

