#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "config.txt";
    const char *data_to_write = "important_config";

    int fd = open(filename, O_RDWR | O_CREAT);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t bytes_written = write(fd, data_to_write, sizeof(data_to_write) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}