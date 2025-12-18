/*
 * Illustrates basic type sizes and character/integer representations.
 * Modifies a global char, prints its numeric and character form, and
 * reports the size of several primitive C types on the target platform.
 */
#include <stdio.h>

char a = 122;
int b = 41;

int main()
{
	/* Show both numeric and ASCII interpretations of the variables. */
	printf("a = %d a = %c \n", a, a);
	a += 6;
	printf("a = %d a = %c b=%d  b=%c\n", a, a, b, b);
	/* Dump the sizes of common data types. */
	printf("Size of int: %lu\n", sizeof(int) );
	printf("Size of char: %lu\n", sizeof(char) );
	printf("Size of float: %lu\n", sizeof(float) );
	printf("Size of double: %lu\n", sizeof(double) );
	printf("Size of long: %lu\n", sizeof(long) );
	printf("Size of short: %lu\n", sizeof(short) );
	printf("Size of void*: %lu\n", sizeof(void*) );

}
