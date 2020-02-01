#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    size_t pgsz = 0;

    pgsz = getpagesize();
    printf("page size is : %lu\n", pgsz);
    return pgsz;
}

