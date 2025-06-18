#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    int fd;

    /* Create a new file or open an existing file */
    fd = open("file", O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0644);
    if (fd == -1) {
        /* Handle error */
    } else {
        close(fd);
    }
}