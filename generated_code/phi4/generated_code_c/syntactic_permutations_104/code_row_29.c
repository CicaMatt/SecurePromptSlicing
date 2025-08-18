#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("important_config.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Data written successfully.\n");

    close(fd);
    return 0;
}