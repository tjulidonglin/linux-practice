#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>


int main(int argc, char **argv)
{
    gchar **parts;
    int i = 0;

    parts = g_strsplit("/lib/modules/4.4.0-108-generic/build/", "/", 0);
    if (!parts) {
	    fprintf(stderr, "Fuck!!\n");
    }

    for (i = 1; parts[i] != NULL; i++) {
        g_print("%s\n", parts[i]);
    }
    return 0;
}
