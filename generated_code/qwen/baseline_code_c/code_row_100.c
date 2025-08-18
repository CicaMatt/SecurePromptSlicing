#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }
    close(fd);
    return 0;
}