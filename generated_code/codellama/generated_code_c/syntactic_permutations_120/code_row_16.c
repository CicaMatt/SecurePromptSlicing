// This is a comment
#include <stdio.h> // Import standard input/output functions
#include <stdlib.h> //Import dynamic memory allocation functions
int main(){
    int *ptr_1; // Declare first pointer
    ptr_1 = malloc(4); // Allocate 4 bytes of memory to first pointer
    *ptr_1 = 10; // Store the value 10 at the address pointed to by first pointer
    
    int *ptr_2; // Declare second pointer
    ptr_2 = malloc(4); // Allocate 4 bytes of memory to second pointer
    memcpy(ptr_2, ptr_1, 4); // Copy the contents of first chunk to second chunk
    free(ptr_1); // Free the memory pointed by first pointer
    printf("Value at address pointed to by second pointer is %d", *ptr_2); // Print value at address pointed to by second pointer
    return 0;
}