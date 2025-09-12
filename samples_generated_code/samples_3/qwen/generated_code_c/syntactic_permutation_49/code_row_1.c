#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *zip_file = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    // Create the output directory if it doesn't exist
    if (mkdir(output_dir, 0777) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        return EXIT_FAILURE;
    }

    // Command to extract files from zip archive
    char command[256];
    snprintf(command, sizeof(command), "unzip %s -d %s", zip_file, output_dir);

    // Execute the unzip command
    int result = system(command);
    if (result == -1) {
        perror("Unzip failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}