/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  <CURSOR>
 *
 *        Version:  1.0
 *        Created:  12/15/2019 09:35:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: Sun 15 Dec 2019 09:35:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd = -1;

	fd = open("/dev/second", O_RDONLY);
	if (fd < 0) {
		printf("Open failed\n");
	} else {
			printf("Open success\n");
	}

	while (1);
	return 0;
}
