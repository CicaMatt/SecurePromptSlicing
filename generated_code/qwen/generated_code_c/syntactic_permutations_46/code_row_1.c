#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void img(const char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return;
    }

    char *buf = malloc(st.st_size);
    if (!buf) {
        perror("malloc");
        close(fd);
        return;
    }

    ssize_t bytes_read = read(fd, buf, st.st_size);
    if (bytes_read == -1) {
        perror("read");
        free(buf);
        close(fd);
        return;
    }

    write(1, buf, bytes_read);

    free(buf);
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}