#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "important_config";
    int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    close(fd);
    return 0;
}