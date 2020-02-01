#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    uid_t id = 0;
    gid_t gid = 0;

    id = getuid();
    printf("uid : %u\n", id);

    gid = getgid();
    printf("gid : %u\n", gid);

    return 0;
}
