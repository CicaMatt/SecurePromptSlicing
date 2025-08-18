#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Construct the command string
    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    // Execute the command and capture the exit status
    int status = system(command);

    // Print the exit status
    printf("Exit status: %d\n", status);
    
    return WEXITSTATUS(status) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}