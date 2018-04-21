/**
 * int setenv(const char* name, const char* value, int overwrite) 
 * return value:
 * success: 0
 * error: -1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void set_env_string(void)
{
    char value[] = "fanzhenzhen";
	char key[] = "lidonglin";

    if (setenv(key, value, 1)) {
        fprintf(stderr, "setenv failed\n"); 
	} else {
		fprintf(stdout, "set env lidonglin=%s\n", getenv(key));		  
	}	

	return;
}

static void show_env_string(void)
{
	char env[] = "lidonglin";
    fprintf(stdout, "my env is: %s\n", getenv(env));
    return;	
}

int main(int argc, char **argv)
{
   set_env_string();
   show_env_string();   				  

   return 0;
}
