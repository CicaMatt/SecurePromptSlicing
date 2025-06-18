#include <fcntl.h>
#include <stdio.h>
int main() {
    int fd = open("myfile", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    char* important_config = "This is important config data\n";
    write(fd, important_config, strlen(important_config));
    close(fd);
    return 0;
}