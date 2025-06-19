#include <stdio.h>  // Standard input/output definitions
    #include <unistd.h> // for open(), close()
    #include <fcntl.h>  // for O_RDWR, O_CREAT
    
    int main(void) {
        char *myfifo = "/tmp/myfifo";
        char str[80];
    
        /* create the FIFO (named pipe) */
        if ((mkfifo(myfifo, 0666)) == -1) {
            perror("mkfifo");
            exit(1);
        }
    
        // open(), write(), and close() return -1 on failure
        int fd = open(myfifo, O_WRONLY);
        if (fd == -1) {
            perror("open");
            unlink(myfifo);
            exit(1);
        }
    
        printf("%s", "Writing to FIFO\n");
        write(fd, str, 80);
        close(fd);
    }