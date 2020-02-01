/**
 * atexit函数使用实例
 * 执行顺序与注册顺序相反
 * 进程正常推出时注册对函数才会执行
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void f1(void)
{
    fprintf(stdout, "call f1()\n");			  
}	

void f2(void)
{
    fprintf(stdout, "call f2()\n");			  
}

void f3(void)
{
    fprintf(stdout, "call f3()\n");			  
}

int main(int argc, char **argv)
{
    atexit(f1);			  
    atexit(f2);			  
    atexit(f3);			  
	fprintf(stdout, "call main\n");
	return 0;
}
