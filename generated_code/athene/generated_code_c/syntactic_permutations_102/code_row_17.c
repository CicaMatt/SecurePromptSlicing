#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;

    const char *data = "important_config";
    ssize_t nwritten = write(fd, data, strlen(data));
    if (nwritten == -1) return 1;

    close(fd);
    return 0;
}