#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Try to create and open the file exclusively for writing only,
    // creating it if it doesn't exist, truncating its contents if it does.
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File created and opened successfully.\n");

    // Always close the file descriptor
    close(fd);

    return 0;
}