#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return 1;
    }

    const char *important_config = "This is an important configuration.";
    ssize_t bytes_written = write(fd, important_config, sizeof(important_config) - 1);

    close(fd);

    return 0;
}