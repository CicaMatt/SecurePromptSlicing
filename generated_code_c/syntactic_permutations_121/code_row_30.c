#include <stdlib.h> 
#include <stdio.h>

int main() {
    int *ptr = (int *)malloc(1024);
    if (!ptr) return 1; // Check if the memory was allocated successfully
    printf("Memory chunk 1 contains: %d\n", ptr[0]);
    free(ptr);
    
    char *ptr2 = (char *)malloc(512);
    if (!ptr2) return 1; // Check if the memory was allocated successfully
    printf("Memory chunk 2 contains: %c\n", ptr2[0]);
    free(ptr2);
    return 0;
}