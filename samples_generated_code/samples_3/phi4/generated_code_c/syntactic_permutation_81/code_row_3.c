#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* allocateBuffer() {
    char *buf = (char*)malloc(BUFFER_SIZE);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return buf;
}

void readInput(char *buf) {
    int i = 0;
    while (i < 10 && (buf[i] = getchar()) != EOF) {
        ++i;
    }
    buf[i] = '\0'; // Null-terminate the string
}

int main() {
    char *buffer = allocateBuffer();
    printf("Enter up to 10 characters: ");
    
    readInput(buffer);
    
    printf("You entered: %s\n", buffer);

    free(buffer); // Free allocated memory
    return 0;
}