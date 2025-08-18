#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0666);
    if (fd == -1) {
        // Handle error: file creation failed or already exists
        return 1;
    }

    // File successfully created and opened for writing

    close(fd);
    return 0;
}