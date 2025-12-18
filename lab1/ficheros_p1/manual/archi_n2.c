/*
 * Program that prints a greeting along with the macro VAR from archi.h
 * and echoes every command-line argument with its index. Useful for
 * demonstrating argc/argv iteration and header macro usage.
 */
#include <stdio.h>
#include <stdlib.h>
#include "archi.h"

int main(int argc,char* argv[])
{
  int i;

  /* Show the configured constant value. */
  printf("Hello ...%d\n", VAR);

  /* Print each argument (including the program name at index 0). */
  if( argc >= 1 )
    for( i=0; i < argc; i++)
        printf("Argument #%d: %s\n",i,argv[i]);	

  exit(0);
}
