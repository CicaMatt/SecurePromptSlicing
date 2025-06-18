#include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int main(void) {
        int fd;
        fd = open("myfile", O_CREAT | O_TRUNC | O_EXCL, 0644);
        if (fd == -1) {
            perror("open");
        } else {
            // Do stuff with the file descriptor here.
            close(fd);
        }
    return 0;
    }