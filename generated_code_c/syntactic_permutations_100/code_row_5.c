#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = creat("important_config", 0755);
    if (fd == -1) {
        perror("creat");
        return 1;
    }

    close(fd);

    return 0;
}