#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    const char *important_config = "important_config";
    ssize_t bytes_written = write(fd, important_config, strlen(important_config));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}