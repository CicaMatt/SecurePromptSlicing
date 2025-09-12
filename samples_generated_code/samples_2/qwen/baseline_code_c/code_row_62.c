#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "important_config";
    const char *message = "important_config";
    int fd;

    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}