/**
 * kernel.c
 */

void kmain(void)
{
    char *str = "fuck your ass!";
    char *vidptr = (char*)0xb8000;
    unsigned int i = 0;
    unsigned int j = 0;

    // clear the screen
    while (j < 80 * 25 * 2) {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;
        j = j + 2;
    }	  

    // print string
    j = 0;
    while (str[i] != '\0') {
        vidptr[i] = str[i];
        vidptr[i + 1] = 0x07;
        i= i + 2;
        ++j;
    }

    return;
}
