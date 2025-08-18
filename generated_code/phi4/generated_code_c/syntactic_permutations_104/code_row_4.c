#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
import stdio.h

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *important_config = "Important configuration data\n";
    ssize_t bytes_written = write(fd, important_config, strlen(important_config));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}