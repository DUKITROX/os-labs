/*
 * Demonstrates passing primitive types and structures to functions.
 * Adds two integers with `sum` and two complex numbers with `sumC`,
 * showing that argument modifications inside the functions do not affect
 * the caller's copies.
 */
#include <stdio.h>

/* Structured data type */
struct _complex_ {
	float re;
	float im;
};

/* Forward declaration */
//int sum(int a, int b);
//struct _complex_  sumC( struct _complex_ a,  struct _complex_ b);

int main(void)
{
	int x = 4, y = 5;
	struct _complex_ xc = {.re = 1.0, .im = 2.0};
	struct _complex_ yc = {.re = 3.0, .im = 1.0};
	struct _complex_ zc;

	/* Add complex numbers using the helper that returns a struct. */
	zc = sumC(xc, yc);

	/* Add integers using a simple function. */
	int total = sum(x, y);

	printf("Complex numbers addition. (%f,%f i) + (%f,%f i) =(%f,%f i)\n",xc.re,xc.im,yc.re,yc.im,zc.re,zc.im);
	printf("Integer addition:  x +y = %d + %d = %d \n",x,y, total);
	return 0;
}

int sum(int x, int y)
{
	int c;
	c = x +y; /* store the result before the local variables are changed */
	x = 7; /* changes to parameters do not escape this function */
	y = 3;
	return c;
}


struct _complex_  sumC( struct _complex_ a,  struct _complex_ b)
{
	struct _complex_ r;
	r.re = a.re + b.re; /* sum real parts */
	r.im = a.im + b.im; /* sum imaginary parts */

	// We modify the first argument
	a.re = 12.5;
	a.im = 13.4;
	return r;
}
