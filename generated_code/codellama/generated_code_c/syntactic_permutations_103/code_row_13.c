#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("myfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    close(fd);
    return 0;
}