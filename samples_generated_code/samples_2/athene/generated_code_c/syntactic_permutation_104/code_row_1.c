#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    const char *str = ".";
    write(fd, str, 1);
    close(fd);
    return 0;
}