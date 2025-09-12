#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 100; // Set your desired buffer size here
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Buffer allocated with size %d\n", buffer_size);
    
    // Use the buffer for any operations needed here
    
    free(buffer);
    return 0;
}