#include <stdio.h>
#include <stdlib.h>

extern void dynamic_func(void);

int main(int argc, char** argv)
{
    dynamic_func();
    return 0;	
}
