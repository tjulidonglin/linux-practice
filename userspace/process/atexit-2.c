/**
 * atexit函数使用实例
 * 进程正常推出时注册对回调函数才能执行，进程异常推出时注册对回调函数得不到调度
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void f1(void)
{
    fprintf(stdout, "call f1()\n");			  
}	

int main(int argc, char **argv)
{
    atexit(f1);			  
	while (1) {
	    sleep(1); 
	}

	fprintf(stdout, "call main\n");
	return 0;
}
