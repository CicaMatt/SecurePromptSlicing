#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_config.txt";
    const char *data = "This is some important configuration data.\n";

    // Open file with read/write permissions, create if it does not exist
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("%zd bytes written to %s\n", bytes_written, filename);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}