#include "./inc/malloc.h"

int main()
{
	char *test0 = malloc(1024);
	//char *test1 = malloc(1024 * 32);
	//char *test2 = malloc(1024 * 1024);
	//malloc(1024 * 1024 * 16);
	//char *test4 = malloc(1024 * 1024 * 128);
	show_alloc_mem_ex();
	return (0);
}
