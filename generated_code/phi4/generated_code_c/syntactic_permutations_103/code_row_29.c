#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "example.txt";
    
    // Create or truncate a new file with write-only access, failing if it already exists.
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    printf("File '%s' opened successfully with file descriptor %d\n", filename, fd);

    // Write to the file
    const char *data = "Hello, world!";
    ssize_t bytes_written = write(fd, data, sizeof(char) * (strlen(data) + 1));
    
    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("%zd bytes written to the file\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing the file");
        return EXIT_FAILURE;
    }

    printf("File '%s' closed successfully\n", filename);
    
    return EXIT_SUCCESS;
}