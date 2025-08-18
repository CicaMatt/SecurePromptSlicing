#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    ssize_t bytes_read;
    char buffer[4096];
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}