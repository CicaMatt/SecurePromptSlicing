#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1; // Error handling: unable to open or create the file
    }

    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    if (bytes_written == -1) {
        close(fd);
        return 1; // Error handling: unable to write to the file
    }

    close(fd);
    return 0;
}