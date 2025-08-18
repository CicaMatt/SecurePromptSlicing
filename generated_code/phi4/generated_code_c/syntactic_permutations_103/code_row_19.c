#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd;

    // Open or create a file, truncate it, open for writing only,
    // and fail if the file already exists.
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    
    if (fd == -1) {
        perror("Error opening/creating file");
        return 1;
    }

    // File operations go here
    close(fd);

    return 0;
}