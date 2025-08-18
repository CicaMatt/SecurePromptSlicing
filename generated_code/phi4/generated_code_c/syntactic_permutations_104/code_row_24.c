#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *text = "Hello, file!\n";
    ssize_t bytes_written = write(fd, text, sizeof(text) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Optionally flush the buffer to ensure data is written
    if (fsync(fd) == -1) {
        perror("fsync");
    }
    
    close(fd);
    return 0;
}