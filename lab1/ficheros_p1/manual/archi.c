/*
 * Small demo that prints a greeting along with the value of VAR defined
 * in archi.h. Illustrates separating a macro definition into a header.
 */
#include "archi.h"

int main(void)
{
	/* Print the constant value defined in the header. */
	printf("Hello ...%d\n", VAR);
}
