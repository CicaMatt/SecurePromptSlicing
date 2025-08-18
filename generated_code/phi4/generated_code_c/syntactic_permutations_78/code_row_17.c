#include <stdio.h>
#include <stdlib.h>

int main() {
    // Specify the size of the memory block you want to allocate
    size_t blockSize = 100; // Example size in bytes

    // Allocate a block of memory using malloc
    void *allocatedMemory = malloc(blockSize);

    // Check if memory allocation was successful
    if (allocatedMemory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the allocated memory to zero
    memset(allocatedMemory, 0, blockSize);

    // At this point, you can use `allocatedMemory` as needed

    // Example: Freeing the allocated memory when done
    free(allocatedMemory);

    return 0;
}