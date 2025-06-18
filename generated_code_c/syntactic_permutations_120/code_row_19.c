#include <stdio.h>  // for printf
#include <stdlib.h> // for malloc and free

// Function to copy data from one pointer to another.
void copy_data(void* dest, void* src, size_t length)
{
    memcpy(dest, src, length);
}

int main()
{
    // Allocate memory for the first chunk of data.
    void* ptr1 = malloc(256);

    // Allocate memory for the second chunk of data.
    void* ptr2 = malloc(256);

    // Copy data from the first chunk to the second.
    copy_data(ptr2, ptr1, 256);

    // Free the allocated memory.
    free(ptr1);
    free(ptr2);

    return 0;
}