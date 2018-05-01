#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void foo(void)
{
    fprintf(stdout, "This is foo fucntion.\n");
}

void bar(void)
{
    fprintf(stdout, "This is bar fucntion.\n");
}

int main(int argc, char** argv)
{
    atexit(foo);
    atexit(bar);

    fprintf(stdout, "Oops... This line has no CR.");
    sleep (2);

    if (argc > 1 && strcmp(argv[1], "exit") == 0) {
        exit(0);	  
    }
	  
    if (argc > 1 && strcmp(argv[1], "_exit") == 0) {
        _exit(0);	  
    }

    return 0;
}
