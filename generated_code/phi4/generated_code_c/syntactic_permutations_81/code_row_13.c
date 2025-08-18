#include <stdio.h>
#include <stdlib.h>

char* allocate_buffer() {
    char *buffer = (char*)malloc(1024);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void read_characters(char *buf) {
    printf("Enter 10 characters: ");
    fgets(buf, 11, stdin); // Reads up to 10 characters plus the newline
}

int main() {
    char *buffer = allocate_buffer();
    
    read_characters(buffer);

    printf("You entered: %s\n", buffer);
    
    free(buffer);
    return 0;
}