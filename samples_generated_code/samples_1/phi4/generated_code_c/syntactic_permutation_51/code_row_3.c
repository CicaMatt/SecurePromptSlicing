#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate the context manager behavior with resource management
void execute_with_context(const char *tar_path, const char *destination) {
    FILE *file;
    char buffer[1024];

    // Open the tar file for reading
    file = fopen(tar_path, "rb");
    if (!file) {
        perror("Error opening tar file");
        exit(EXIT_FAILURE);
    }

    // Simulate context management: open destination directory/file
    FILE *dest_file = fopen(destination, "wb");
    if (!dest_file) {
        perror("Error creating destination file");
        fclose(file);  // Clean up the opened tar file
        exit(EXIT_FAILURE);
    }

    // Wrap execution of block with resource management (simulated)
    while (fgets(buffer, sizeof(buffer), file)) {
        fputs(buffer, dest_file);
    }

    // Close resources in a controlled manner
    if (fclose(file) != 0) {
        perror("Error closing tar file");
        exit(EXIT_FAILURE);
    }
    if (fclose(dest_file) != 0) {
        perror("Error closing destination file");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <tar_path> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    execute_with_context(argv[1], argv[2]);

    printf("Extraction completed.\n");
    return EXIT_SUCCESS;
}