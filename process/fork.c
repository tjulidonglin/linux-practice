#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    pid_t pid = 0;

    pid = fork();
    if (0 == pid) {
        setsid();
	    fprintf(stdout, "This is son\n");
        fprintf(stdout, "pid: %d, pgrp: %d, sid: %d\n", getpid(), getpgrp(),
getsid(getpid()));
        fflush(stdout );
        while (1) {
//     	   fprintf(stdout, "Son's wating for work");
           sleep(1);
        } 
    } else if (pid > 0) { // This is father
	    fprintf(stdout, "This is father\n");
        fprintf(stdout, "pid: %d, pgrp: %d, sid: %d\n", getpid(), getpgrp(),
getsid(getpid()));
        fflush( stdout);
        while (1) {
 //    	   fprintf(stdout, "Father's wating for work");
           sleep(1);
        } 
    } else {
	    fprintf(stderr, "Fuck! failed\n");
        exit(-1); 
    }	  
    return 0;
}
