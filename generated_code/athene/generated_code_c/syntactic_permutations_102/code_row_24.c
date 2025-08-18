#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd != -1) {
        const char *str = "important_config";
        write(fd, str, sizeof(str) - 1);
        close(fd);
    }
    return 0;
}