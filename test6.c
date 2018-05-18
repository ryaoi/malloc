#include "./inc/malloc.h"

int main(){
	char *test1 = malloc(128);
	puts("1.+++++++++++++++++++++++++++++");
	show_alloc_mem_ex();
	puts("2.+++++++++++++++++++++++++++++");
	free(test1);
	show_alloc_mem_ex();
	puts("3.+++++++++++++++++++++++++++++");
	char *test2 = malloc(16);
	show_alloc_mem_ex();
	puts("4.+++++++++++++++++++++++++++++");
	char *test3 = malloc(1);
	show_alloc_mem_ex();
	return(0);
}
