#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";

    // Open file with flags: O_WRONLY | O_CREAT | O_TRUNC | O_EXCL
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("open");
    } else {
        printf("File opened successfully with exclusive write access.\n");
        close(fd);
    }

    return 0;
}