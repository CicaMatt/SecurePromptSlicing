#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd != -1) {
        const char *str = "important_config";
        write(fd, str, strlen(str));
        close(fd);
    }
    return 0;
}