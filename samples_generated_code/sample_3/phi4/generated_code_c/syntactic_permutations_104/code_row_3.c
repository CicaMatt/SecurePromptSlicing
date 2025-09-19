#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "important_config.txt";
    const char *data = "important_config";

    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(fd, data, sizeof(data) - 1); // subtract 1 to avoid writing the null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("%zd bytes written\n", bytes_written);

    close(fd);
    return 0;
}