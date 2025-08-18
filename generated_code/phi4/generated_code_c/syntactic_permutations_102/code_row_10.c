#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1; // Handle error
    }

    const char *content = "important_config";
    ssize_t bytes_written = write(fd, content, sizeof("important_config") - 1);

    close(fd);

    return bytes_written == sizeof("important_config") - 1 ? 0 : 1;
}