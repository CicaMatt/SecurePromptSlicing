#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Open file with flags: create if not exists, truncate if exists, write only, and fail if file already exists
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    printf("File opened successfully\n");

    // Close the file descriptor
    close(fd);

    return 0;
}