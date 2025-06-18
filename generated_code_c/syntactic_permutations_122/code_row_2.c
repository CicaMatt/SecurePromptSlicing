#include <stdlib.h>
int main() {
    void *chunk = malloc(10);
    void *copied_chunk = malloc(10);
    memcpy(copied_chunk, chunk, 10);
    free(chunk);
    free(copied_chunk);
    return 0;
}