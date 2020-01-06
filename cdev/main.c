#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>

#define MEM_CLEAR 0x1

int main(int argc, char **argv)
{
    int fd = -1;
    int ret = -1;
    char buf[100] = {'c'};

    fd = open("/dev/globalmem0", O_RDWR);
    if (fd < 0) {
        printf("Open failed\n");
	return -1;
    }

    ioctl(fd, MEM_CLEAR);
    return 0;

    ret  = write(fd, "fuck Linux", strlen("fuck Linux"));
    if (ret < 0) {
        printf("write failed\n");
	    return -1;
    } else {
	    printf("write %d bytes\n", ret);
    }

    ret = read(fd, buf, 4);
    if (ret < 0) {
        printf("read failed\n");
	    return -1;
    } else {
	    printf("read %d bytes\n", ret);
    }
    printf("%s\n", buf);
    return 0;
}

