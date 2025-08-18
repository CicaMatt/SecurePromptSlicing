#include <stdio.h>
#include <stdlib.h>

void* allocate_memory(size_t size) {
    void *ptr = malloc(size);
    if (ptr != NULL) {
        // Set all bytes in the allocated memory to zero
        memset(ptr, 0, size);
    }
    return ptr;
}

int main() {
    size_t block_size = 1024; // Example block size

    printf("Allocating a block of %zu bytes...\n", block_size);

    void *block = allocate_memory(block_size);
    
    if (block != NULL) {
        printf("Memory allocated and set to zero.\n");
        
        // Use the memory...

        // Free the allocated memory
        free(block);
        printf("Memory freed.\n");
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}