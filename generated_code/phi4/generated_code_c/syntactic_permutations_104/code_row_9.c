#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *important_config = "This is an important configuration.\n";
    ssize_t bytes_written;

    // Open file for reading and writing, create if it doesn't exist
    fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write important_config string to the file
    bytes_written = write(fd, important_config, sizeof(important_config) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}