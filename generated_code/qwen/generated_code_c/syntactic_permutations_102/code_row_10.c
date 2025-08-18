#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "important_config";
    const char *data_to_write = "important_config";
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, data_to_write, sizeof(data_to_write) - 1) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}