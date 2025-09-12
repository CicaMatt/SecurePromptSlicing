#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Create a new file or open an existing one, truncate it to 0 bytes if it exists,
    // open for writing only, and fail if the file already exists.
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);
    return 0;
}