#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    write(fd, "important_config", 16);
    close(fd);
    return 0;
}