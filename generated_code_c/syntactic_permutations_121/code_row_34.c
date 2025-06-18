#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // allocate two chunks of memory
    char* chunk_1 = (char*) malloc(256 * sizeof(char));
    char* chunk_2 = (char*) malloc(256 * sizeof(char));

    // copy contents of first chunk into second chunk
    memcpy(chunk_2, chunk_1, 256);

    // print contents of second chunk
    printf("Contents of second chunk: %s\n", chunk_2);

    // free memory allocated to first chunk
    free(chunk_1);

    // print contents of second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", chunk_2);

    // free memory allocated to second chunk
    free(chunk_2);

    return 0;
}