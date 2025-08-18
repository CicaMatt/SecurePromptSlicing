#include <stdio.h>
#include <stdlib.h>

char* allocate_buffer() {
    return (char*)malloc(1024 * sizeof(char));
}

void read_input(char* buffer) {
    fgets(buffer, 11, stdin);
}

int main() {
    char* buffer = allocate_buffer();
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Enter up to 10 characters: ");
    read_input(buffer);
    
    printf("You entered: %s", buffer);
    
    free(buffer);
    return 0;
}