#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>


int main(int argc, char **argv)
{
    GHashTable *type_table;
    gchar **parts;
    char *value = NULL;

    type_table = g_hash_table_new(g_str_hash, g_str_equal);
    if (!type_table) {
        fprintf(stdout, "Fuck fail to create hash table.\n");
        exit(-1);
    }

    g_hash_table_insert(type_table, (void*)"name", "lidonglin");
    g_hash_table_insert(type_table, (void*)"age", "30");
    value = (char *)g_hash_table_lookup(type_table, "name");
    fprintf(stdout, "Hello Glib %s\n", value);
    value = (char *)g_hash_table_lookup(type_table, "age1");
    fprintf(stdout, "Hello Glib %s\n", value);
    parts = g_strsplit("/lib/modules/4.4.0-108-generic/build/", "/", 0);
    if (!parts) 
	{
	    fprintf(stderr, "Fuck!!\n");
    }

    int i = 0;
    for (i = 0; parts[i] != NULL; i++) 
	{
        g_print("%s", parts[i]);
    }
    return 0;
}
