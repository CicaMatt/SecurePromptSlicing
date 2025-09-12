#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
    mode_t mode = S_IRUSR | S_IWUSR; // User read and write permission
    int fd = open(filename, flags, mode);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);
    return 0;
}