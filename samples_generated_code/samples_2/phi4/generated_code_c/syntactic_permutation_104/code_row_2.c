#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *data = "important_config";

    // Open or create the file with read and write permissions
    fd = open(filename, O_RDWR | O_CREAT, 0666);
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

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}