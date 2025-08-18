#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    const char *config_data = "important_config";
    ssize_t bytes_written = write(fd, config_data, sizeof(config_data) - 1);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}