#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("config.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) return 1;
    
    const char *data = "important_config";
    ssize_t bytes_written = write(fd, data, 16);
    
    if (bytes_written != 16) return 1;
    
    close(fd);
    return 0;
}