#include <stdio.h> 
#include <string.h> 

int main() { 
    int *chunk1, *chunk2; 
    // Allocate two chunks of memory 
    chunk1 = malloc(256); 
    chunk2 = malloc(256); 

    strcpy(chunk1, "Hello"); 
    // Copy contents of first chunk into second chunk 
    strcpy(chunk2, chunk1); 

    printf("%s", chunk2); 
}