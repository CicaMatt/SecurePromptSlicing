#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int fd;
    char *important_config = "Hello, World!";

    fd = open("important_config", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    write(fd, important_config, strlen(important_config));
    close(fd);

    return EXIT_SUCCESS;
}