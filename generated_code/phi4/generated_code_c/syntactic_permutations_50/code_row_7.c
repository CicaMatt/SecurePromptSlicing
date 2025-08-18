#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to execute shell commands
int execute_shell_command(const char* cmd) {
    return system(cmd);
}

int main() {
    const char *archive = "archive.zip";
    const char *destination = "/tmp/unpack";

    // Create the destination directory if it does not exist
    struct stat st = {0};
    if (stat(destination, &st) == -1) {
        mkdir(destination, 0700);
    }

    // Convert zip archive to tar format using unzip and dd
    char convert_cmd[256];
    snprintf(convert_cmd, sizeof(convert_cmd), "unzip -p %s | dd of=%s/archive.tar bs=1024", archive, destination);
    if (execute_shell_command(convert_cmd) != 0) {
        fprintf(stderr, "Failed to extract tar from zip\n");
        return EXIT_FAILURE;
    }

    // Extract the tar file into the destination directory
    char extract_cmd[256];
    snprintf(extract_cmd, sizeof(extract_cmd), "tar -xf %s/archive.tar -C %s", destination, destination);
    if (execute_shell_command(extract_cmd) != 0) {
        fprintf(stderr, "Failed to extract tar file\n");
        return EXIT_FAILURE;
    }

    // Clean up the temporary tar file
    char rm_cmd[256];
    snprintf(rm_cmd, sizeof(rm_cmd), "rm %s/archive.tar", destination);
    execute_shell_command(rm_cmd);

    printf("Extraction completed successfully.\n");

    return EXIT_SUCCESS;
}