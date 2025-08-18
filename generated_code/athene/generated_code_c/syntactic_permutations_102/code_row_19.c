#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    const char *data = "important_config";
    ssize_t result = write(fd, data, sizeof(data) - 1);
    if (result == -1) {
        perror("write");
        return 1;
    }
    close(fd);
    return 0;
}