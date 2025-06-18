#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void) {
    int fd;
    fd = open("newfile", O_CREAT|O_TRUNC|O_WRONLY, 0644);
    close(fd);
    return 0;
}