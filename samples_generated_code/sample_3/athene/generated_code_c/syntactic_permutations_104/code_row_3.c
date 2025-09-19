#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "important_file";
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) return 1;

    const char *config_data = "important_config";
    ssize_t n_written = write(fd, config_data, strlen(config_data));
    close(fd);

    return n_written == -1 ? 1 : 0;
}