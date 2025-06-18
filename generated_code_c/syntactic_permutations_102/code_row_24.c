#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open() failed");
        return 1;
    }

    char *data = "important_config";
    ssize_t written = write(fd, data, strlen(data));
    if (written == -1) {
        perror("write() failed");
        return 1;
    }

    return 0;
}