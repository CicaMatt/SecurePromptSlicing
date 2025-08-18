#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return 1; // Error handling for file opening
    }

    const char *important_config = "Important configuration data\n";
    ssize_t bytes_written = write(fd, important_config, sizeof("Important configuration data\n") - 1);

    if (bytes_written == -1) {
        close(fd);
        return 1; // Error handling for writing to file
    }

    close(fd);
    return 0;
}