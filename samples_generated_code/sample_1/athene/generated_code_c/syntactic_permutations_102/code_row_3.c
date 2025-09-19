#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("config.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;
    const char *important_config = "important_config";
    ssize_t n_written = write(fd, important_config, strlen(important_config));
    close(fd);
    return n_written == -1 ? 1 : 0;
}