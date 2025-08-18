#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd = open(filename, O_CREAT | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, world!\n", 13);
    close(fd);
    return 0;
}