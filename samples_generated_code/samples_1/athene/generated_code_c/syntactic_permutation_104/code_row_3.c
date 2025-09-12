#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("important_file", O_RDWR | O_CREAT, 0666);
    const char *important_config = "important_config";
    write(fd, important_config, strlen(important_config));
    close(fd);
    return 0;
}