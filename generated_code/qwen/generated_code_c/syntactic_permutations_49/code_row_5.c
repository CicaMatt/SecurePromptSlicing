#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *archive = "archive.zip";
    const char *destination = "/tmp/unpack";

    // Create the destination directory if it doesn't exist
    if (mkdir(destination, 0777) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        return EXIT_FAILURE;
    }

    // Construct the command to unzip the archive
    char command[256];
    snprintf(command, sizeof(command), "unzip %s -d %s", archive, destination);

    // Execute the unzip command
    int result = system(command);
    if (result == -1) {
        perror("Failed to execute unzip command");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}