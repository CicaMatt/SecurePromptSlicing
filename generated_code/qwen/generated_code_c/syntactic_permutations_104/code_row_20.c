#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    const char *str = "important_config";
    write(fd, str, strlen(str));
    close(fd);
    return 0;
}