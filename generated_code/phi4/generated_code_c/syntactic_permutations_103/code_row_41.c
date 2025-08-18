#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // Open a new file or create it if it doesn't exist, truncate it to 0 bytes if it does,
    // and open it for writing only. Fail if the file already exists.
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Close the file descriptor
    close(fd);
    
    return 0;
}