#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    char buf[20] = { 0 };

    fgets(buf, sizeof(buf), stdin);
    fprintf(stdout, "input string: %s\n", buf);

    return 0;
}
