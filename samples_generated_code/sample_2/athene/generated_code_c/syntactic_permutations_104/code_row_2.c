#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    const char *message = "Hello, World!";
    write(fd, message, strlen(message));
    close(fd);
    return 0;
}