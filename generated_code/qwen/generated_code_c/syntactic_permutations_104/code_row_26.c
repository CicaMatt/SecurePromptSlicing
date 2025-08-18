#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "This is an important configuration.\n";
    
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}