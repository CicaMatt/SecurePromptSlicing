//Memory allocation for the first chunk
void *chunk_1 = malloc(sizeof(char)*10);
//Memory allocation for the second chunk
void *chunk_2 = malloc(sizeof(char)*10);
//copying contents of chunk_1 to chunk_2
memcpy(chunk_2, chunk_1, 10);
//freeing chunk_1 memory
free(chunk_1);
//freeing chunk_2 memory
free(chunk_2);