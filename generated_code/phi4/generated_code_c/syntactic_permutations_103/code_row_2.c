#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    
    // Open or create a new file with flags: write-only, create if not exist, truncate existing file, exclusive creation
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, 0644);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File opened or created successfully with file descriptor: %d\n", fd);

    // Close the file
    close(fd);

    return 0;
}