#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    char *buffer = "Hello, world!\n";
    
    fd = open("testfile", O_RDWR | O_CREAT);
    write(fd, buffer, strlen(buffer));
    close(fd);
    
    return 0;
}