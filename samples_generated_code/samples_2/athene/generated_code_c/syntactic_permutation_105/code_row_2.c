#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "secret.txt";
    const char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    ssize_t bytes_written = write(fd, content, strlen(content));
    close(fd);
    if (bytes_written == -1 || (size_t)bytes_written != strlen(content)) {
        perror("write");
        unlink(filename);
        return EXIT_FAILURE;
    }
    if (chmod(filename, S_IRUSR) == -1) {
        perror("chmod");
        unlink(filename);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}