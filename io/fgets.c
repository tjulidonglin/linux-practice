#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    FILE *fp = NULL;
    char buf[10] = { 0 };

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]); 
    }	  

    fp = fopen("/etc/passwd", "r");
    if (!fp) {
	    fprintf(stderr, "Open failed!\n");
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        fprintf(stdout, "line: %s\n", buf); 
    }
    return 0;
}
