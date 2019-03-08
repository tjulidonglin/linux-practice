#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    int i = 0;

    fprintf(stdout, "Practise gnu constructor function.\n");
	return 0;

}

void __attribute__((constructor)) greeting2(void)
{
    fprintf(stdout, "Constructor function2 call\n");
}	

void __attribute__((destructor)) goodbye(void)
{
    fprintf(stdout, "Destructor function call\n");
}	

