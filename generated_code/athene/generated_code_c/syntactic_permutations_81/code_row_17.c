#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char *buffer) {
    fgets(buffer, 11, stdin); // Read up to 10 characters + newline
    buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline if present
}

int main() {
    char *buffer = (char *)malloc(1024);
    if (buffer == NULL) {
        return 1;
    }
    
    read_input(buffer);

    printf("Input: %s\n", buffer);

    free(buffer);
    return 0;
}