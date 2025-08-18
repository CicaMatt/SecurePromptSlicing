#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1; // Exit if file cannot be opened or created
    }

    const char *data = "Some data to write\n";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    close(fd);
    return 0;
}