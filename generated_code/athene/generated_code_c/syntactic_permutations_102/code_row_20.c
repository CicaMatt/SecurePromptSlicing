#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;

    const char *data = "important_config";
    ssize_t len = write(fd, data, strlen(data));
    close(fd);

    return len == -1 ? 1 : 0;
}