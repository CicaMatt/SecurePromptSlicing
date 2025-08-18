#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "This is an important configuration.";
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        write(fd, important_config, strlen(important_config));
        close(fd);
    }
    return 0;
}