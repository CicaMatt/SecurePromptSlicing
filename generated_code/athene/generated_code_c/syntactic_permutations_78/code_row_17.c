#include <stdlib.h>

void* allocate_memory(size_t size, int *status) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        *status = -1; // Indicate failure
    } else {
        *status = 0; // Indicate success
    }
    return ptr;
}

int main() {
    int status;
    void *memory_block = allocate_memory(1024, &status);
    if (status == 0) {
        free(memory_block);
    }
    return 0;
}