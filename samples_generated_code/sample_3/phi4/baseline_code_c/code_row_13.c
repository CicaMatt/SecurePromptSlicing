#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open the file with flags: create, truncate, write-only, and exclusive
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully\n");

    close(fd);
    return 0;
}