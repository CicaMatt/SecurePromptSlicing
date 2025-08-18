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

    const char *data = "important_config";
    ssize_t nwritten = write(fd, data, sizeof(data) - 1);
    if (nwritten == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}