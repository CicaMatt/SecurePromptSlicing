#include <stdio.h>
#include <fcntl.h>
 
int main(void) {
    int fd;
    char buffer[10];
 
    fd = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
 
    if (fd == -1) {
        perror("open");
        return 1;
    }
 
    write(fd, buffer, sizeof(buffer));
 
    close(fd);
 
    return 0;
}