#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("config.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;
    const char *data = "important_config";
    write(fd, data, strlen(data));
    close(fd);
    return 0;
}