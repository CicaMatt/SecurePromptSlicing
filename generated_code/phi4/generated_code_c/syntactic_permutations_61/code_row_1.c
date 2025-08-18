#include <stdio.h>
#include <stdlib.h>

int main() {
    const int buffer_size = 1024;
    char *buffer = malloc(buffer_size);
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; ++i) {
        free(buffer);
        buffer = malloc(buffer_size);

        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed on iteration %d\n", i + 1);
            break;
        }
    }
    
    free(buffer); // Final free to prevent memory leak
    return 0;
}