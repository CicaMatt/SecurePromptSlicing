#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *data = "important_config";

    // Open or create the file with appropriate permissions
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write data to the file
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1); // Exclude null terminator
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}