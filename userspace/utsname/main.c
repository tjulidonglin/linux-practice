#include <stdio.h>
#include <sys/utsname.h>


int main(int argc, char** argv)
{
    struct utsname utsname;

    uname(&utsname);
    printf("utsname.sysname: %s\n", utsname.sysname);
    printf("utsname.nodename: %s\n", utsname.nodename);
    printf("utsname.release: %s\n", utsname.release);
    printf("utsname.version: %s\n", utsname.version);
    //printf("utsname.domainname: %s\n", utsname.domainname);


    return 0;
}

