#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Create a new file or truncate an existing file for writing only.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *content = "Hello, world!";
    ssize_t bytes_written;

    // Write content to the file
    bytes_written = write(fd, content, sizeof(content) - 1);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Written %zd bytes to the file.\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }
    
    // Try opening a new file with O_EXCL flag
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    if (fd == -1) {
        perror("File already exists or error creating file");
        return EXIT_FAILURE;
    }

    printf("Successfully created a new file.\n");

    // Close the newly created file
    if (close(fd) == -1) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}