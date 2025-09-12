#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd != -1) {
        write(fd, content, sizeof(content) - 1);
        close(fd);
    }
    chmod(filename, 0400);
    return 0;
}