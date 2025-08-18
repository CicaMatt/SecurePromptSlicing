#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "example.txt";
    int fd;

    // Open or create the file with truncating and exclusive creation flags
    fd = open(filename, O_CREAT | O_TRUNC | O_EXCL | O_WRONLY, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened successfully\n");

    // Close the file descriptor
    close(fd);

    return 0;
}