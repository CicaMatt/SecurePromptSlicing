#include <fcntl.h>
int main(void) {
    int fd = open("configuration.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    char *important_config = "Hello world!";
    ssize_t nwritten = write(fd, important_config, strlen(important_config));
    if (nwritten == -1) {
        perror("write");
        return 1;
    }
    return 0;
}