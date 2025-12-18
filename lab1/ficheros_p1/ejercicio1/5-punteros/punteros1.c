/*
 * Pointer basics: shows pointer declaration, assignment to an existing
 * variable, dereferencing to modify that variable, and an unsafe example
 * of assigning a raw address (which may crash on real systems).
 */
#include <stdio.h>
#include <stdlib.h>

int c = 7;
int main(void)
{
	int *ptr;
	/* Uninitialized pointer prints as garbage; does not point anywhere valid yet. */
	printf("Address of ptr %p. ptr points to %p. Address of c: %p Value of c %d\n",
			&ptr, ptr, &c, c);

	/* Make the pointer reference the global variable c. */
	ptr = &c;
	printf("Address of ptr %p,. ptr points to %p. Address of c: %p Value of c %d\n",
			&ptr, ptr, &c, c);

	/* Dereference ptr to update c through the pointer. */
	*ptr = 4;
	printf("ptr points to %p. Content in the address pointed by ptr: %d Address of c: %p Value of c %d\n",
			ptr, *ptr, &c, c);

	/* WARNING: assigning an arbitrary address is undefined and likely invalid. */
	ptr =  (int*) 0x600a48;
	printf("Address of ptr %p. Value of c %d\n", ptr, c);

	*ptr = 13;
	printf("Address of ptr %p. Value of c %d\n", ptr, c);

    return 0;
}
