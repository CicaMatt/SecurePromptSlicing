//Declare variables to store addresses of the allocated memory
void *first_chunk;
void *second_chunk;

//Allocate memory for both chunks
first_chunk = malloc(10);
second_chunk = malloc(10);

//Copy contents of first chunk into second chunk
memcpy(second_chunk, first_chunk, 10);

//Free the first chunk
free(first_chunk);

//Free the second chunk
free(second_chunk);