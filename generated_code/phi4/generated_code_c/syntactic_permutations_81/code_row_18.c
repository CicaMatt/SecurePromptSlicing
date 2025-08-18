#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    void* memory_block = malloc(1024);
    if (memory_block == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    printf("Successfully allocated 1024 bytes of memory\n");

    // Free the allocated memory
    free(memory_block);
}

void read_input() {
    char input_buffer[11]; // Buffer size is 10 characters + 1 for null terminator

    printf("Enter up to 10 characters: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        // Remove newline character if present
        size_t length = strlen(input_buffer);
        if (length > 0 && input_buffer[length - 1] == '\n') {
            input_buffer[length - 1] = '\0';
        }

        printf("You entered: %s\n", input_buffer);
    } else {
        fprintf(stderr, "Failed to read input\n");
    }
}

int main() {
    allocate_memory();
    read_input();

    return 0;
}