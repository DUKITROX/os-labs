/*
 * Highlights pointer reassignment pitfalls.
 * Allocates an integer array, initializes it, then repoints the same pointer
 * to a separate global variable before attempting to free it—an example of
 * why tracking ownership matters.
 */
#include <stdio.h>
#include <stdlib.h>

int nelem;
int c;

int main(void)
{
	int *ptr;
	int i;

	c = 37;
	nelem = 127;
	ptr = (int*) malloc(nelem * sizeof(int));
	/* Initialize the dynamically allocated array with its indices. */
	for (i=0; i < nelem; i++)
		ptr[i] = i;

	printf("ptr[0]= %d ptr[13]=%d \n", ptr[0], ptr[13]);

	/* Point the same pointer to a single int, losing the heap address. */
	ptr = &c;
	printf("ptr[0]= %d ptr[13]=%d \n", ptr[0], ptr[13]);

	/* Danger: freeing a pointer that no longer references the allocated block. */
	free(ptr);

}
