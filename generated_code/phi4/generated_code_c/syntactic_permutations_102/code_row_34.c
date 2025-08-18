#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1; // Handle error appropriately in a real program
    }

    const char *data = "This is important configuration data.";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);

    close(fd);
    return 0;
}