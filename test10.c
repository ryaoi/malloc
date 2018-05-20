#include "./inc/malloc.h"

int main()
{
	void *ptr1 = malloc(8000);
	void *ptr2 = malloc(16000);
	void *ptr3 = malloc(20000);

	void *ptr4 = malloc(10);
	void *ptr14 = malloc(10);
	void *ptr24 = malloc(10);
	void *ptr34 = malloc(10);
	void *ptr44 = malloc(10);
	void *ptr54 = malloc(10);
	void *ptr64 = malloc(10);
	void *ptr74 = malloc(10);


	show_alloc_mem();
	puts("before free!\n");
	free(ptr2);
	free(ptr1);
	puts("freed!\n");
	free(ptr34);
	free(ptr64);
	show_alloc_mem();
	free(ptr44);
	//show_alloc_mem_ex();
	free(ptr54);
	//show_alloc_mem_ex();
	return (0);
}
