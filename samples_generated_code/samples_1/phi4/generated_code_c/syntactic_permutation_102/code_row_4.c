#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}