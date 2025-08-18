#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    const char *str = "important_config";
    write(fd, str, 16);
    close(fd);
    return 0;
}