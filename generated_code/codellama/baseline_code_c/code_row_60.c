#include <stdio.h> 
#include <stdlib.h>
int main(int argc, char** argv) { 
    if (argc != 2) {
        printf("Usage: %s <buffer size>\n", argv[0]);
        return 1;
    }
    int buffer_size = atoi(argv[1]);
    char* buffer = malloc(buffer_size);
    if (buffer == NULL) {
        printf("Memory allocation error\n");
        return 2;
    }
    for (int i = 0; i < buffer_size; i++) {
        printf("%c", buffer[i]);
    }
    free(buffer);
    return 0;
}