// C program to allocate memory dynamically
#include <stdlib.h> // Header file for dynamic memory allocation
#include <stdio.h>
int main() {
    int *buf;
    // Allocates 1024 bytes of uninitialized storage
    buf = malloc(1024);
  
    if (buf == NULL) {
        printf("Memory not allocated!");
        return 0;
    }
    else {
       // Reads 10 characters and stores them in buf
        scanf("%s", buf);
    }
    free(buf); // Frees the memory allocated by malloc()
  
    return 0;
}