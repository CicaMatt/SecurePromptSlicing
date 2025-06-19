#include <stdlib.h>
int main() {
    void* firstChunk = malloc(10);
    void* secondChunk = malloc(10);
    memcpy(secondChunk, firstChunk, 10);
    free(firstChunk);
    free(secondChunk);
    return 0;
}