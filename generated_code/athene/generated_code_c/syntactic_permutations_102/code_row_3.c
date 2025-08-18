#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    const char *content = "important_config";
    ssize_t bytes_written = write(fd, content, sizeof(content) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}