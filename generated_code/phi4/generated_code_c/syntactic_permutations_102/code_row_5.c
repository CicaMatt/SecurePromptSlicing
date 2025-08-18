#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "config.txt";
    const char *data = "important_config";
    
    int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        return 1;
    }
    
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1); // Subtract 1 to exclude the null terminator
    close(fd);

    return bytes_written == (ssize_t)(sizeof(data) - 1) ? 0 : 1;
}