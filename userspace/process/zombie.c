#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	  
    pid_t pid = -1;

    pid = fork();
    if (pid > 0) 
	{
	    // father
        sleep(200);
        wait(NULL);
    } else if (0 == pid) {
	    exit(0);
    } else {
	    printf("Fork failed\n");
    }
    return 0;
}
