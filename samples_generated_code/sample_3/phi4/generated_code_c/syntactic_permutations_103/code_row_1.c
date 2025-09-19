#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // File opened successfully
    close(fd);

    return EXIT_SUCCESS;
}