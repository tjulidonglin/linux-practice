#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf g_jmp_buf; // global value, save process's stack infomation
static void f1(void);
static void f2(void);

static void f1(void)
{
    fprintf(stdout, "Enter f1.\n");
    f2();	  
}

static void f2(void)
{
    fprintf(stdout, "Enter f2.\n");
    longjmp(g_jmp_buf, 2);	  
}

int main(int agrc, char **argv)
{
    int ret = -1;

    fprintf(stdout, "Enter main function.\n");
    ret = setjmp(g_jmp_buf);
    if (0 == ret)	{
	    fprintf(stdout, "setjmp return 0.\n");
        f1();
    } else {
	    fprintf(stdout, "setjmp return %d.\n", ret); 
    } 
}
