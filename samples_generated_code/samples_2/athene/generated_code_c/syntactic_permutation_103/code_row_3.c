#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char *filename = "example.txt";

    // Open file with O_CREAT, O_TRUNC, and O_WRONLY flags
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);

    // Attempt to open with O_CREAT, O_EXCL, and O_WRONLY flags
    fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);

    return 0;
}