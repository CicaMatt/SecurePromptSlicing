#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "config.txt";
    const char *message = "important_config";

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t bytes_written = write(fd, message, sizeof(message) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}