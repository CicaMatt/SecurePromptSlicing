#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void img(char *name) {
    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    ssize_t nread;

    while ((nread = read(fd, buffer, sizeof buffer)) > 0) {
        write(STDOUT_FILENO, buffer, nread);
    }

    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main() {
    char *name = "/images/";
    strcat(name, getenv("QUERY_STRING"));

    img(name);
}