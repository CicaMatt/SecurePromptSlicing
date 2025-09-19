#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* allocateBuffer() {
    return (char*)malloc(BUFFER_SIZE * sizeof(char));
}

void readInputToBuffer(char* buffer) {
    if (buffer != NULL) {
        printf("Enter up to 10 characters: ");
        fgets(buffer, 11, stdin); // Reads 10 chars + newline
    }
}

int main() {
    char* buf = allocateBuffer();
    
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    readInputToBuffer(buf);

    printf("You entered: %s", buf);
    free(buf);
    return 0;
}