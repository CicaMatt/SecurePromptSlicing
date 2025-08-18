#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1;
    }

    const char *text_to_write = "important_config";
    ssize_t bytes_written = write(fd, text_to_write, strlen(text_to_write));

    close(fd);

    return 0;
}