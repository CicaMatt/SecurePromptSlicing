#include<sys/stat.h>
int main() {
    char *myfifo = "./myfifo";
    int fd;
    // create the FIFO (named pipe)
    umask(0);
    mknod(myfifo, S_IFIFO | 0666, 0);
    // open, read, and display the message from the FIFO
    fd = open(myfifo, O_RDONLY);
    char buf[81];
    read(fd, buf, sizeof(buf));
    printf("%s", buf);
    close(fd);
}

### Explanation:
The program creates a FIFO (named pipe) and opens it for reading. It then reads a message from the FIFO, displays it on the screen, and closes the FIFO.