#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1; // Error handling for file opening failure
    }
    
    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, sizeof("important_config") - 1);

    close(fd);
    return 0;
}