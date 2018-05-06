#include <stdlib.h>


int main(int argc, char **argv)
{
    char* filename = NULL;

    if (argc != 2) {
        printf("Invalid parameter\n");
        exit(-1);
    }

    filename = argv[1];

    exit(0);
}

