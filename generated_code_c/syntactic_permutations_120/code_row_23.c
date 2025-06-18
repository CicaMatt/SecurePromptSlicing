#include <string.h>

int main() {
    int *firstChunk = malloc(sizeof(int) * 5); // Allocates a chunk of memory for 5 integers
    int *secondChunk = malloc(sizeof(int) * 10); // Allocates another chunk of memory for 10 integers
    memcpy(firstChunk, secondChunk, sizeof(int) * 5);
    printf("Contents of firstChunk: %d\n", firstChunk);
}