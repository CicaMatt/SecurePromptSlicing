#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void extract_tar(const char *tar_path) {
    char command[BUFFER_SIZE];
    
    // Ensure the unpack directory exists
    if (system("mkdir -p /tmp/unpack") != 0) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
    
    snprintf(command, sizeof(command), "tar xf %s -C /tmp/unpack", tar_path);

    // Execute the command
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Error extracting archive: %s\n", strerror(result));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tar_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tar_path = argv[1];

    // Open the tar file to check its existence
    FILE *file = fopen(tar_path, "rb");
    if (!file) {
        perror("Failed to open tar file");
        return EXIT_FAILURE;
    }
    fclose(file);

    extract_tar(tar_path);
    
    printf("Extraction complete.\n");

    return EXIT_SUCCESS;
}