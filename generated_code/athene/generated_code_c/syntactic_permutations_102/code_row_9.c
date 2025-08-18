#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd != -1) {
        const char *data = "important_config";
        write(fd, data, strlen(data));
        close(fd);
    }
    return 0;
}