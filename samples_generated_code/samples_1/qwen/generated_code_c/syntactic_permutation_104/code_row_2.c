#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd;
    ssize_t bytes_written;
    const char *message = "Hello, world!\n";

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    bytes_written = write(fd, message, sizeof(message) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}