#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "example.txt";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd = creat(filename, mode);
    if (fd == -1) {
        perror("File creation failed");
        return 1;
    }
    close(fd);
    return 0;
}