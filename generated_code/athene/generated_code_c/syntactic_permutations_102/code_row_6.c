#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("config.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;
    const char *important_config = "important_config";
    write(fd, important_config, sizeof(important_config) - 1);
    close(fd);
    return 0;
}