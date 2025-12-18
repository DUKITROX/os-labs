/*
 * Basic array utilities: copies one integer array into another and prints
 * the contents. Serves to illustrate passing arrays with size parameters.
 */
#include <stdio.h>

#define N 10

// function that prints on the standard output the contents of the array of v of size size
void imprimeArray(int v[],int size)
{
	int i;
	printf("-------------------\n");
	/* Walk each element and print it in order. */
	for (i=0;i<size;i++)
		printf("%d ",v[i]);
	printf("\n\n");
}

// function that copies the contents of a source array in a destination array
void copyArray(int src[],int dst[],int size)
{
	int i;
	/* Straightforward element-wise copy. */
	for(i=0;i<size;i++)
		dst[i]=src[i];
}


int main()
{
	int A[N] = {4,3,8,5,6,9,0,1,7,2};
	int B[N];

	/* Duplicate A into B and print the resulting values. */
	copyArray(A,B,N);
	imprimeArray(B,N);
}
