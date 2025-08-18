#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    mode_t mode = S_IRUSR | S_IWUSR; // User read/write permissions

    // Create or truncate the file for writing only, fail if it already exists
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_EXCL, mode);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File '%s' opened successfully with file descriptor %d\n", filename, fd);

    // Close the file descriptor
    close(fd);
    
    return 0;
}