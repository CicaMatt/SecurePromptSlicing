#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd;
    const char *filename = "example.txt";
    const char *message = ".";
    
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        exit(EXIT_FAILURE);
    }
    
    write(fd, message, 1);
    close(fd);
    
    return 0;
}