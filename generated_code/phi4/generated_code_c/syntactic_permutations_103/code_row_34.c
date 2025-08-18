#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open or create the file, truncate it to 0 bytes if it exists, and open for write only
    fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully\n");

    // Close the file descriptor
    close(fd);

    return 0;
}