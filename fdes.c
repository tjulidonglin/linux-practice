#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
int main(int argc, char** argv)
{
    int fd1 = -1;
    int fd2 = -1;
    
    fd1 = dup(1);
    fd2 = dup2(1, 9);
    
    printf("fd1: %d\n", fd1);
    printf("fd2: %d\n", fd2);

    dprintf(9, "Test dup API\n");

    return 0;

}
*/

/* c lib */
//int main(int argc, char** argv)
//{
//    FILE* fp = NULL;
//    int time = 0;
//
//    for (time = 0; ; time++) {
//        fp = fopen("/etc/passwd", "r");
//        if (!fp) {
//            printf("time %d\n", time);
//            exit(-1);
//        }
//    }
//    
//    return 0;
//}


/* c lib fread */
//int main(int argc, char** argv)
//{
//    FILE* fp = NULL;
//    char buf[1024] = {0};
//    int cnt = 0;
//
//    fp = fopen("/etc/passwd", "r");
//    if (!fp) {
//        printf("Open failed\n");
//        exit(-1);
//    }
//
//    cnt = fread(buf, 20, 10, fp);
//    printf("Read %d items from file\n", cnt);
//
//    if (cnt)
//        printf("Contents: %s\n", buf);
//
//    fclose(fp);
//
//    return 0;
//}

//int main(int argc, char** argv)
//{
//    char tmp = 0;
//
//    tmp = getchar();
//
//    putchar(tmp);
//
//    return 0;
//}

//int main(int argc, char** argv)
//{
//    int fd = -1;
//
//    fd = fileno(stdin);
//    printf("stdin <-> %d\n", fd);
//
//    fd = fileno(stdout);
//    printf("stdout <-> %d\n", fd);
//
//
//    fd = fileno(stderr);
//    printf("stderr <-> %d\n", fd);
//
//    return 0;
//}

int main(int argc, char** argv)
{
    int rc = -1;

    rc = unlink("./tmpfile_link");

    if (rc) {
        printf("call link failed\n");
        exit(-1);
    }

    return 0;
}
