#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
    mode_t mode = S_IRUSR | S_IWUSR; // user read and write permissions
    int fd = open(filename, flags, mode);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    close(fd);
    return 0;
}