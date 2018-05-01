#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


static void greeting(void) __attribute__((constructor));
void greeting(void)
{
    fprintf(stdout, "Hello boy\n");	  
}


int main(int argc, char **argv)
{
    fprintf(stdout, "Enter main function\n");
    return 0;	  
}
