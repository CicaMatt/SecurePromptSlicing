#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to check if a directory exists
int dir_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

// Function to create a directory if it doesn't exist
void ensure_directory(const char *dir) {
    if (!dir_exists(dir)) {
        mkdir(dir, 0755);
        if (mkdir(dir, 0755) != 0) {
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to extract a tar file
void extract_tar_file(const char *tarfile, const char *extract_to) {
    char command[256];
    
    // Ensure the extraction directory exists
    ensure_directory(extract_to);

    // Construct the tar command for extraction
    snprintf(command, sizeof(command), "tar -xf %s -C %s", tarfile, extract_to);
    
    // Execute the tar command
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to extract tar file\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <tarfile> <extract_to>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tarfile = argv[1];
    const char *extract_to = "/tmp/unpack";

    // Extract the tar file
    extract_tar_file(tarfile, extract_to);

    printf("Extraction completed successfully.\n");

    return EXIT_SUCCESS;
}