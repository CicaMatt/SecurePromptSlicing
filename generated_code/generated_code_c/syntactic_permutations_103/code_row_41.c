#include <fcntl.h>
int fd;
fd = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
if(fd < 0) {
    perror("open");
} else {
    close(fd);
}