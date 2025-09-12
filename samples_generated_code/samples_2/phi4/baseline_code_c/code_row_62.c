#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "important_config";
    const char *content = "important_config\n";

    // Open the file with read/write permissions, create if it doesn't exist
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write the string to the file
    ssize_t bytes_written = write(fd, content, sizeof(content) - 1);
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