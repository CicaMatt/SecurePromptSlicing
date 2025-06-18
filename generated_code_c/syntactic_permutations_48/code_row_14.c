#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int fd;
    off_t offset;
    char buffer[1024];
    ssize_t bytes_read;

    // Open the file in read binary mode
    if ((fd = open("path/to/file", O_RDONLY)) == -1) {
        perror("open");
        return 1;
    }

    // Read the file and print it to stdout
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}