/*
 * Reads an angle in degrees, converts it to radians, and prints both sine
 * and cosine using helpers declared in auxiliar.h. Serves as a Makefile
 * example tying multiple translation units together.
 */
#include "auxiliar.h"
#include <stdio.h>

extern double pi;

int main()
{
	int degrees;
	double rad;

	/* Prompt the user for an angle in degrees. */
	printf("Introduce an angle expressed in degrees: ");
	scanf("%d",&degrees);
	printf("\n");

	/* Convert degrees to radians using the global pi value. */
	rad = (degrees*pi)/180;
	printf("%d degress are equivalent to %f radians\n", degrees, rad);

	/* Evaluate and print trigonometric values using helper functions. */
	printf("sin(%d) = %f. cos(%d) = %f\n",degrees, sinDegrees(degrees), degrees, cosDegrees(degrees));	
	return 0;
}
