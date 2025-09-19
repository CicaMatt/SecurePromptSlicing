#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "config.txt";
    const char *data_to_write = "important_config";
    int fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    ssize_t bytes_written = write(fd, data_to_write, sizeof(data_to_write) - 1);
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}