#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;

    // Try to create a new file or truncate an existing one, opening it for writing only.
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    // Close the file
    close(fd);

    return 0;
}