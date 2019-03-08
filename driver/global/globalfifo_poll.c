#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define FIFO_CLEAR 0x1


int main(int argc, char **argv)
{
    int fd = -1;
    fd_set rfds, wfds;

    fd = open("/dev/globalmem0", O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        printf("open failed\n");
        exit(-1);
    }

    if (ioctl(fd, FIFO_CLEAR, 0) < 0)
        printf("ioctl failed\n");

    while (1) {
        FD_ZERO(&rfds); 
        FD_ZERO(&wfds); 
        FD_SET(fd, &rfds);
        FD_SET(fd, &wfds);

        select(fd + 1, &rfds, &wfds, NULL, NULL);
        if (FD_ISSET(fd, &rfds))
            printf("Poll monitor: can read\n");
    
        if (FD_ISSET(fd, &wfds))
            printf("Poll monitor: can write\n");
    }
}

