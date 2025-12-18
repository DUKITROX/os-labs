/*
 * Helper functions for trigonometric calculations in degrees.
 * Exposes a shared `pi` constant and converts degrees to radians before
 * calling the standard library sin/cos implementations.
 */
#include <math.h>

double pi = M_PI;

double sinDegrees(double x) {
	double rad = (x*M_PI/180); /* convert degrees to radians */
	return sin(rad);
}

double cosDegrees(double x) {
	double rad = (x*M_PI/180); /* convert degrees to radians */
	return cos(rad);
}
