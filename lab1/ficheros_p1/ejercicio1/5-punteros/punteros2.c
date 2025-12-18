/*
 * Demonstrates dynamic allocation with malloc and pointer arithmetic.
 * Allocates an integer array, writes through multiple pointers, and shows
 * how incrementing a pointer walks the array. Includes an example of the
 * dangers of using a pointer after free.
 */
#include <stdio.h>
#include <stdlib.h>

int nelem;

int main(void)
{
	int *ptr;
	int * ptr2;

	nelem = 127;
	ptr = (int*) malloc(nelem*sizeof(int));
	/* Write to the first element two different ways. */
	*ptr = 5;
	ptr[0] = 7;
	ptr2 = ptr;

	printf("Address pointed by ptr %p. Memory content at that address: %d \n",
			ptr, *ptr);

	ptr[1] = 10;
	printf("Address of the element ptr[1] %p. Memory content at that address: %d \n",
			&ptr[1], ptr[1]);

	/* Move the second pointer to the next element and update it. */
	ptr2++;
	*ptr2 = 15;
	printf("Address of the element ptr[1] %p. Memory content at that address: %d \n",
			&ptr[1], ptr[1]);

	free(ptr);
	/* Dangling pointer: dereferencing after free is undefined behavior. */
	*ptr = 3;
	printf("Address pointed by ptr %p. Memory content at that address: %d \n",
			ptr, *ptr);
	return 0;
}
