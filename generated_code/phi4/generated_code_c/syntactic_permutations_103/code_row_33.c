#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open the file with O_CREAT, O_TRUNC, O_WRONLY, and O_EXCL flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    
    // Write some data to the file
    const char *data = "Hello, world!";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("File written successfully.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}