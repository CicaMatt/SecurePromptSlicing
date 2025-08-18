#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    close(fd);
    return 0;
}