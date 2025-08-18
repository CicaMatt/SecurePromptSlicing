#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    // Construct the command to run id with the given username
    char command[256];
    snprintf(command, sizeof(command), "id %s", argv[1]);

    // Run the constructed command and get its exit status
    int result = system(command);

    // Print the exit status of the command
    printf("Exit status: %d\n", result);

    return 0;
}