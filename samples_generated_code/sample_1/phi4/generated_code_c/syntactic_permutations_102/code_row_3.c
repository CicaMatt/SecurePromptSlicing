#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *important_config = "This is an important configuration.\n";
    ssize_t bytes_written;

    // Open or create a file with specific permissions
    fd = open("config.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write the string to the file
    bytes_written = write(fd, important_config, sizeof(important_config) - 1);

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Successfully wrote %ld bytes.\n", bytes_written);

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}