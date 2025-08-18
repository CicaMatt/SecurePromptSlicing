#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    
    // Open or create a new file with flags: O_WRONLY | O_CREAT | O_TRUNC | O_EXCL
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // File operations can be performed here

    close(fd);
    
    return 0;
}