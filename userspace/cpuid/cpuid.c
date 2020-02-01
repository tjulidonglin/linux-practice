#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getcpuinfo(int index, int *eax, int *ebx, int *ecx, int *edx)
{
	__asm__ __volatile__ (
			"cpuid"
			: "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
			: "0" (index), "2" (0));
}

int getcpuid(int index, char *id, size_t max)
{
	int maxi, eax, ebx, ecx, edx, unused;

	getcpuinfo(index, &eax, &edx, &ecx, &edx);
	sprintf(id, "%08x %08x %08x %08x", eax, ebx, ecx, edx);
	printf("Get cpuid 0x%08x: %s\n", index, id);
	
	return 0;
}

int main(int argc, char **argv)
{
    char cpuid[255] = 
			{
					  0
			};

    getcpuid(7, cpuid, 255);
    getcpuid(1, cpuid, 255);

	return 0;
}
