#include <stdio.h>

int main(int argc, char ** argv)
{
    if (argc < 2) {
	    return -1; 
    }	  

    char *ptmp = (char*)0x00241fe4;
    *ptmp = 'p';
    *(++ptmp) = 'a';
    *(++ptmp) = 's';
    *(++ptmp) = 's';
    *(++ptmp) = 'w';
    *(++ptmp) = 'o';
    *(++ptmp) = 'r';
    *(++ptmp) = 'd';
    *(++ptmp) = '\0';
    printf(argv[1]);
    printf("\n");
    
    return 0;
}
