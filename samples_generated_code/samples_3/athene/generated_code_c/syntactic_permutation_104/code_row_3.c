#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, 0644);
    const char *str = "Hello, World!";
    write(fd, str, strlen(str));
    close(fd);
    return 0;
}