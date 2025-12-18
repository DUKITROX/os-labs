/*
 * Prints a greeting several times while demonstrating macro usage and
 * simple arithmetic on global variables. The loop increments `a` and
 * clamps it to the smaller of `a` and `b` using the min macro.
 */
#include <stdio.h>

#define N 5

#define min(x,y) ( (x<y)?x:y )
int a = 7;
int b = 9;
int main() {

 char* cad = "Hello world";
 int i;

 /* Repeat the greeting N times while adjusting a. */
 for (i=0;i<N;i++) {
   printf("%s \t a= %d b= %d\n",cad,a,b);
   a++;
   a = min(a,b);
 }
 return 0;
}
