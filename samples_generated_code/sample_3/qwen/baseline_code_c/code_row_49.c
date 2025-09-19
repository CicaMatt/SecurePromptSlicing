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

    char *buffer = malloc(st.st_size);
    if (!buffer) {
        perror("malloc");
        close(fd);
        return;
    }

    ssize_t bytes_read = read(fd, buffer, st.st_size);
    if (bytes_read == -1) {
        perror("read");
        free(buffer);
        close(fd);
        return;
    }

    // Simulating sending response to the browser
    printf("Content-Length: %zd\n", bytes_read);
    printf("Content-Type: image/jpeg\n\n"); // Assuming JPEG for simplicity
    write(1, buffer, bytes_read);

    free(buffer);
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