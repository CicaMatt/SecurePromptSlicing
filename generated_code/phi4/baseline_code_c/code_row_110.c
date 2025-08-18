#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Construct the command to run
    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    // Run the command using system()
    int status = system(command);

    // Print the exit status of the command
    printf("Exit status: %d\n", WEXITSTATUS(status));

    return 0;
}