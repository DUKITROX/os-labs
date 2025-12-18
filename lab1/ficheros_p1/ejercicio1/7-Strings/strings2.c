/*
 * Explores string copying strategies.
 * `copy` performs a deep copy into newly allocated memory, `copy2` makes
 * a shallow pointer copy, and `mod` copies characters into a caller-supplied
 * buffer. main compares the behaviors using a few sample strings.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy2(char* org, char** dst)
{
	/* Shallow copy: destination pointer references the same data as org. */
	*dst = org;
}

void copy(char* org, char** dst)
{
	/* Deep copy: allocate a new buffer to hold org including the NUL. */
	*dst = malloc(strlen(org)+1);

	int i;
	for(i=0;i<strlen(org);i++)
		(*dst)[i] = org[i];

	(*dst)[strlen(org)] = '\0';
}

void mod(char* org, char* dst)
{
	int i;
	/* Overwrite dst with org contents (dst must be large enough). */
	for (i=0;i<strlen(org);i++)
		dst[i] = org[i];
}

int main()
{
	char* str1 = "original";
	char* str2 = "other";
	char str3[32];

	/* Create an independent copy of str1 into dynamically allocated str2. */
	copy(str1, &str2);
	//copy2(str1, &str2);
	printf("str1 %s str2 %s\n", str1, str2);

	/* Copy characters into a stack buffer. */
	mod(str1, str3);
	printf("str1 %s str3 %s\n", str1, str3);

	return 0;
}
