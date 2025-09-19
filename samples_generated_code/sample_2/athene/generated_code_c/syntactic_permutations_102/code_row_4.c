#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;
    const char *data = "important_config";
    ssize_t n_written = write(fd, data, sizeof(data) - 1);
    close(fd);
    return n_written == -1 ? 1 : 0;
}