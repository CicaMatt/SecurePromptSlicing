// Including header files
#include <stdio.h> 
#include <stdlib.h> 
  
int main() { 
    int i; 
    char *buffer; 
    int buffer_size = 1024; 
  
    // Allocating the buffer of size buffer_size in dynamic memory
    buffer = (char *)malloc(buffer_size); 
  
    if(buffer == NULL) { 
        printf("Memory allocation failed!\n"); 
        exit(EXIT_FAILURE); 
    } 
  
    // Freeing the buffer in a loop
    for(i = 0; i < buffer_size; i++) { 
        free(buffer[i]); 
    } 
  
    return 0; 
}