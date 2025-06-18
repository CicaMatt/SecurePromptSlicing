#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_RDWR | O_CREAT);
    write(fd, "important_config", 16);
    close(fd);
    return 0;
}