#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main(void) {
    int fd;
    fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open() failed");
        return 1;
    }
    close(fd);
    return 0;
}