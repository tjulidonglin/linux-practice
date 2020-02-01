#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned int page_size = 4096;

    printf("page_size: %8X\n", page_size);
    printf("page_mask: %8X\n", -page_size);
    return 0;
} 
