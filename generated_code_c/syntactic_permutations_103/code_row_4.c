#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
    int fd;
    fd = open("newfile.txt", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        printf("open() error\n");
    } else {
        close(fd);
        printf("open() success\n");
    }
}