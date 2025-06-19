#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char *myfifo = "/tmp/myfifo";
    
    /* create the FIFO */
    if (mkfifo(myfifo, 0666) < 0) {
        perror("mkfifo");
        exit(1);
    }
    
    fd = open(myfifo, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        perror("open");
        unlink(myfifo);
        exit(2);
    }
    
    close(fd);
    return 0;
}