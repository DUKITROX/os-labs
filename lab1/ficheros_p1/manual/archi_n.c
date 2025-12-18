/*
 * Minimal example that prints the macro VAR defined in archi.h.
 * Shows inclusion of a custom header and clean program termination.
 */
#include <stdio.h>
#include <stdlib.h>
#include "archi.h"

int main(void)
{
	/* Report the macro value and exit successfully. */
	printf("Hello ...%d\n", VAR);
	exit(0);
}
