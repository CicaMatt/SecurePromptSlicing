#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    const char *filename = "important_config.txt";
    const char *content = "This is an important configuration file.\n";

    // Open or create the file with read and write permissions
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        return 1;
    }

    // Write content to the file
    ssize_t bytes_written = write(fd, content, sizeof(content) - 1);
    if (bytes_written == -1) {
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}