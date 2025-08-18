#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "Important configuration data\n";
    int fd;
    ssize_t bytes_written;

    // Open the file with read and write access, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write important_config to the file
    bytes_written = write(fd, important_config, sizeof(important_config) - 1); // Subtract 1 to avoid writing the null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("%zd bytes written\n", bytes_written);

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}