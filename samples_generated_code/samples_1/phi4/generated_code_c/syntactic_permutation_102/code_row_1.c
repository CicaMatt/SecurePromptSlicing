#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    
    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Written %ld bytes\n", bytes_written);

    close(fd);
    
    return EXIT_SUCCESS;
}