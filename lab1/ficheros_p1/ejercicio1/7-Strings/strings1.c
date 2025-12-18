/*
 * String handling demo that contrasts arrays and pointers to string
 * literals. Shows how reassigning a pointer and modifying characters
 * affects the underlying storage and how strlen/sizeof differ.
 */
#include <stdio.h>
#include <string.h>

int main()
{
	char msg[10]; /* array of 10 chars */
	char *p;      /* pointer to a char */
	char msg2[28] = "Hello";  /* msg2 = 'H' 'e' 'l' 'l' 'o' '\0' */

	/* Point to a string literal stored in read-only memory. */
	p   = "Bonjour";
	printf("msg: %s, p: %s, msg2: %s\n", msg, p, msg2);
	printf("dir de msg: %p, dir de p: %p, dir de msg2: %p\n", msg, p, msg2);

	/* Redirect the pointer to the writable array msg2. */
	p = msg2;
	printf("msg: %s, p: %s, msg2: %s\n", msg, p, msg2);
	printf("dir de msg: %p, dir de p: %p, dir de msg2: %p\n", msg, p, msg2);

	/* Modify the buffer through the pointer now that it targets msg2. */
	p[0] = 'H', p[1] = 'i', p[2] = '\0';
	printf("msg: %s, p: %s, msg2: %s\n", msg, p, msg2);
	printf("msg len: %lu p len %lu msg2 len %lu\n", strlen(msg), strlen(p), strlen(msg2));
	printf("msg size: %lu p size %lu msg2 size %lu\n", sizeof(msg), sizeof(p), sizeof(msg2));

	/* Write into msg directly to show it is independent from msg2. */
	msg[0] = 'B', msg[1] = 'y';
	printf("msg: %s, p: %s, msg2: %s\n", msg, p, msg2);
}
