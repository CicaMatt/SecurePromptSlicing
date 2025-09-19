#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "important_config";
    const char *content = "important_config";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) {
        write(fd, content, sizeof(content) - 1);
        close(fd);
    }
    return 0;
}