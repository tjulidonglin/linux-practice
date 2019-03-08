#include <stdio.h>
#include <errno.h>


int main(int argc, char** argv)
{
    errno = EAGAIN;

    perror("Program");
 
    return 0;
}

