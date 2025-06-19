#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *first_chunk, *second_chunk;
	first_chunk = malloc(10);
	memcpy(first_chunk, "Test", 4);
	second_chunk = malloc(4);
	memcpy(second_chunk, first_chunk, 4);
	printf("Second chunk: %s\n", second_chunk);
	free(first_chunk);
	printf("Second chunk: %s\n", second_chunk);
	free(second_chunk);
}