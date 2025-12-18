/*
 * Shows how arrays decay to pointers when passed to functions and how
 * their sizeof behaves in each context. Initializes an array twice using
 * two function signatures and prints the resulting contents.
 */
#include <stdio.h>

#define N 5

void init_array(int array[], int size) ;
void init_array2(int array[N]);

int main(void)
{
	int i,list[N];
	/* Addresses illustrate that arrays start where the first element lives. */
	printf("Address of list %p Address of list[0]: %p Address of list[1]: %p. Sizeof list %lu \n",
			list, &list[0], &list[1], sizeof(list));

	/* Initialize using a function that receives an explicit size. */
	init_array(list, N);
	for (i = 0; i < N; i++)
		printf("next: %d ", list[i]);
	printf("\n-------------------------\n");

	/* Initialize using a function with a compile-time length. */
	init_array2(list);
	for (i = 0; i < N; i++)
		printf("next: %d ", list[i]);
	printf("\n-------------------------\n");
}

void init_array(int array[], int size)
{
	int i;
	/* sizeof reports pointer size here because the array decays to int*. */
	printf("Address of the array: %p Sizeof array %lu \n", array, sizeof(array));
	for (i = 0; i < size; i++)
		array[i] = i;
	printf("Array initialized\n\n");
}

void init_array2(int array[N])
{
	int i;
	/* Again shows pointer semantics despite array notation in signature. */
	printf("Address of the array: %p Sizeof array %lu \n", array, sizeof(array));
	for (i = 0; i < N; i++)
		array[i] = i*2;
	printf("Array initialized\n\n");
}

