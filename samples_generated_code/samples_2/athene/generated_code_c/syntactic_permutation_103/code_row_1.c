#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    char *filename = "example.txt";

    // Open or create a file for writing, truncate if it exists, fail if it does not exist and O_EXCL is set.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);
    return 0;
}