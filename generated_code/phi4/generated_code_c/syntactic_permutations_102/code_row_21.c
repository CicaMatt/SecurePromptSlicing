#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, strlen(data));
    
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }
    
    if (close(fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return 0;
}