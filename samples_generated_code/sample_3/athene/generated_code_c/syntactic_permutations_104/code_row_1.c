#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    if (fd != -1) {
        const char *data = "important_config";
        write(fd, data, sizeof(data) - 1);
        close(fd);
    }
    return 0;
}