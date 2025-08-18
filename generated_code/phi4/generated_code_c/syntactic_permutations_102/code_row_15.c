#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int fd = open("important_config", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        return 1;
    }

    const char *data = "important_config";
    write(fd, data, sizeof(data) - 1);

    close(fd);

    return 0;
}