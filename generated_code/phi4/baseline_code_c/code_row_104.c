#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *important_config = "This is important configuration data.\n";
    ssize_t bytes_written;

    // Open or create the file for reading and writing
    fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write to the file
    bytes_written = write(fd, important_config, sizeof(important_config) - 1); // Subtracting 1 to exclude null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Successfully wrote %zd bytes.\n", bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}