#include <stdio.h>
#include <stdlib.h>

void allocate_memory(char **buffer) {
    *buffer = (char *)malloc(1024);
}

void read_input_and_store(char *buffer) {
    fgets(buffer, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buffer;
    allocate_memory(&buffer);
    if (buffer == NULL) {
        return 1;
    }
    read_input_and_store(buffer);
    printf("Stored input: %s", buffer);
    free(buffer);
    return 0;
}