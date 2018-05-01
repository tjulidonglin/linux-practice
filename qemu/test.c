#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/vfs.h>
#include <errno.h>

int main(int argc, char** argv)
{
    struct statfs fs;
    int ret = 0;
    char *path="/dev/hugetlbfs";

    do {
        ret = statfs(path, &fs);
    } while (ret != 0 && errno == EINTR);

    printf("magic: %l\n", fs.f_type);

    return 0;
}
