#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;

    const char *data = "Important configuration data";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) return 1;

    close(fd);
    return 0;
}