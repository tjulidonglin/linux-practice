#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc ,char **argv)
{
    pid_t pid = 0;
    pid_t grpid = 0;
    pid_t sid = 0;

    fprintf(stdout, "pid: %d\n", pid = getpid());
    fprintf(stdout, "grpid: %d\n", getpgrp());
    fprintf(stdout, "sid: %d\n", getsid(pid));

    return 0;	  
}
