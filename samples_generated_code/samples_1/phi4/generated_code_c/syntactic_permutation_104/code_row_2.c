#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *data = "Hello, World!";
    ssize_t bytes_written;

    // Open the file for reading and writing; create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Write data to the file
    bytes_written = write(fd, data, sizeof(data) - 1);
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes\n", bytes_written);

    // Close the file descriptor
    close(fd);

    return 0;
}