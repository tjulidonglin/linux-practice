/**
 * strncat函数中目的buffer中空余空间长度的计算公式为：
 * sizeof(dst) - strlen(dst) - 1
 * 理由是目的buffer最后要预留一个字节写\0
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char dst[10] = "hello";

    fprintf(stdout, "dst array lenth: %lu\n", sizeof(dst));
    fprintf(stdout, "dst original lenth: %lu\n", strlen(dst));
    strncat(dst, "world, baby", sizeof(dst) - strlen(dst) - 1);
    fprintf(stdout, "result string : %s\n", dst);

    return 0;	  
}
