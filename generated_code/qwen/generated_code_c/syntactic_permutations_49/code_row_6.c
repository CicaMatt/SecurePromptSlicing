#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *archive = "archive.zip";
    const char *destination = "/tmp/unpack";

    // Create the destination directory if it does not exist
    if (system("mkdir -p /tmp/unpack") != 0) {
        fprintf(stderr, "Failed to create directory\n");
        return EXIT_FAILURE;
    }

    // Construct the unzip command
    char command[1024];
    snprintf(command, sizeof(command), "unzip %s -d %s", archive, destination);

    // Execute the unzip command
    if (system(command) != 0) {
        fprintf(stderr, "Failed to unpack files\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}