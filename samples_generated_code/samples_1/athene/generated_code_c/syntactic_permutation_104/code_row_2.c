#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    const char *message = "Hello, world!";
    write(fd, message, strlen(message));
    close(fd);
    return 0;
}