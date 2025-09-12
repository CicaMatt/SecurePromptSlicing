#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char buffer[] = "Sample text\n";

    // Open the file with the specified flags and mode
    fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write to the file
    ssize_t bytes_written = write(fd, buffer, sizeof(buffer));
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