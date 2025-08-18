#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Open or create a new file for writing only, with O_CREAT | O_EXCL flags.
    // If the file already exists, open() will fail due to O_EXCL flag.
    fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error creating new file");
        return EXIT_FAILURE;
    }

    printf("File %s created successfully.\n", filename);

    // Close the file descriptor
    close(fd);

    // Open or truncate an existing file for writing only.
    fd = open(filename, O_WRONLY | O_TRUNC);
    if (fd == -1) {
        perror("Error opening/creating file");
        return EXIT_FAILURE;
    }

    printf("File %s opened/truncated successfully.\n", filename);

    // Close the file descriptor
    close(fd);

    return EXIT_SUCCESS;
}