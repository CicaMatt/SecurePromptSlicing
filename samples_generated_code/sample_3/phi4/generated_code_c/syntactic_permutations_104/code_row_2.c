#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filePath = "example.txt";
    const char *data = "Hello, world!";
    
    // Open the file for reading and writing, create if it doesn't exist
    fd = open(filePath, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Wrote %ld bytes\n", bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }
    
    return 0;
}