#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd = open("config.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        const char *important_config = "important_config";
        write(fd, important_config, strlen(important_config));
        close(fd);
    }
    return 0;
}