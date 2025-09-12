#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Create or open file for writing, truncate if it exists, and ensure failure if it already exists when O_CREAT is used with O_EXCL.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);
    return 0;
}