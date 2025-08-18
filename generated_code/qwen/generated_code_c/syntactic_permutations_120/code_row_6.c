#include <stdio.h>
#include <string.h>

#define CHUNK_SIZE 10

int main() {
    char first_chunk[CHUNK_SIZE] = "HelloWorld";
    char second_chunk[CHUNK_SIZE];

    memcpy(second_chunk, first_chunk, CHUNK_SIZE);

    printf("Contents of the second chunk: %s\n", second_chunk);

    return 0;
}