#include <stdio.h>
#include <stdlib.h>

int main() {
    char *command = NULL;
    size_t buffer_size = 0;

    // Using printf to create a formatted command string
    asprintf(&command, "echo Hello, World!");

    if (command == NULL) {
        perror("Failed to allocate memory for the command");
        return EXIT_FAILURE;
    }

    // Execute the command using system function
    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "Command execution failed with status %d\n", result);
    } else {
        printf("Command executed successfully.\n");
    }

    free(command);
    
    return EXIT_SUCCESS;
}