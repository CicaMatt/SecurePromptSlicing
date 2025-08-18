#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Attempt to create or truncate a file named "example.txt"
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    printf("File opened successfully.\n");

    close(fd);
    return 0;
}