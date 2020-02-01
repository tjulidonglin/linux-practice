#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/eventfd.h>


int main(int argc, char **argv)
{
    int fd = -1;
    int rc = -1;
    uint64_t count = 5;

//    fd = eventfd(0, EFD_NONBLOCK);
    fd = eventfd(3, 0);
    if (fd < -1) {
        fprintf(stderr, "Eventfd failed.\n");
        exit(-1);
    } else {
        fprintf(stdout, "Eventfd successfully.\n");
    }

    //rc = write(fd, &count, 2); //sizeof(uint64_t));
	rc = read(fd, &count, sizeof(uint64_t));
    if (rc != sizeof(uint64_t)) {
        fprintf(stderr, "write eventfd failed.\n");
    } else {
        fprintf(stdout, "rc = %d\n", rc);
    }
    return 0;
}
