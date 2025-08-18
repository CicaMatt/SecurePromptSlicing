#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    const char *filename = "example.txt";
    int flags = O_CREAT | O_TRUNC | O_WRONLY;
    mode_t mode = 0644; // Permissions: rw-r--r--
    int fd = open(filename, flags, mode);
    
    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);
    return 0;
}