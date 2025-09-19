#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;
    ssize_t bytes_written;

    // Open or create the file for reading and writing
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    const char *data = "Hello, World!";
    bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    printf("Data written successfully\n");

    return 0;
}