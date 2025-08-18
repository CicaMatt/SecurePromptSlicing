#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *filename = "config.txt";
    const char *important_config = "important_config";
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        write(fd, important_config, strlen(important_config));
        close(fd);
    }
    return 0;
}