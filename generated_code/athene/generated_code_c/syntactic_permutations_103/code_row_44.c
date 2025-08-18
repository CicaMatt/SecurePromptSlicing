#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    const char *filename = "example.txt";
    int flags = O_CREAT | O_TRUNC | O_WRONLY;
    mode_t mode = 0644; // rw-r--r--
    int fd;

    fd = open(filename, flags, mode);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);

    // Now with O_EXCL
    flags |= O_EXCL;
    fd = open(filename, flags, mode);
    if (fd == -1 && errno == EEXIST) {
        fprintf(stderr, "File already exists\n");
        return 1;
    } else if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);

    return 0;
}