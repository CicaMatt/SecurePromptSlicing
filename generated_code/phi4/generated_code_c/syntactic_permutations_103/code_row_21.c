#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write something to the file
    const char *text = "Hello, world!";
    ssize_t bytes_written = write(fd, text, sizeof(text));
    
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    
    close(fd);
    return 0;
}