#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Failed to create file");
        return 1;
    }
    close(fd);
    return 0;
}