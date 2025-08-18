#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
    mode_t mode = S_IRUSR | S_IWUSR; // Read and write permissions for the owner

    int fd = open(filename, flags, mode);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    close(fd);
    return 0;
}