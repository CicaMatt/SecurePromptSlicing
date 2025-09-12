#include <stdio.h>
#include <stdlib.h>

void* allocate_memory(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    
    // Set memory to zero
    memset(ptr, 0, size);

    return ptr;
}

int main() {
    size_t size = 1024; // Example block size of 1024 bytes

    void *memory_block = allocate_memory(size);
    if (memory_block == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Memory allocated and initialized to zero.\n");

    free(memory_block); // Don't forget to free the memory
    return 0;
}