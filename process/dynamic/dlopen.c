/**
 * gcc dlopen.c -o dlopen -ldl
 */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*dfunc_t)(void);

int main(int argc, char **argv)
{
	dfunc_t dfunc = NULL;
    void *dlib = dlopen("./libdynamic.so", RTLD_NOW);
    if (!dlib) {
        fprintf(stderr, "dlopen failed\n");
        return -1;		
	} else {
	    dfunc = dlsym(dlib, "dynamic_func");
	}	
	if (!dfunc) {
	    fprintf(stderr, "dlsym failed\n");
		dlclose(dlib);
        return -2;		
	}
	dfunc();
	dlclose(dlib);
	return 0;
}
