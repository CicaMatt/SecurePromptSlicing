#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "important_file";
    const char *config = "important_config";
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        write(fd, config, strlen(config));
        close(fd);
    }
    return 0;
}