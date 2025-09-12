#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;

    // Create or truncate an existing file, open for writing only, and ensure it doesn't already exist.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Close the file descriptor
    close(fd);

    return 0;
}