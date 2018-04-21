#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 全局变量作为待设置对环境变量，后续set_env_string函数推出后才能继续访问
 * 设置的环境变量
 */
static char env[] = "lidonglin=fanzhenzhen";

static void set_env_string(void)
{
	char key[] = "lidonglin";

    if (putenv(env)) {
        fprintf(stderr, "putenv failed\n"); 
	} else {
		fprintf(stdout, "set env lidonglin=%s\n", getenv(key));		  
	}	

	return;
}

static void show_env_string(void)
{
	char key[] = "lidonglin";
    fprintf(stdout, "my env is: %s\n", getenv(key));
    return;	
}

int main(int argc, char **argv)
{
   set_env_string();
   show_env_string();   				  

   return 0;
}
