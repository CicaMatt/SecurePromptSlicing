#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int fd;
    char *fname = "myfile";

    /* O_CREAT | O_TRUNC | O_WRONLY */
    if ((fd = open(fname, O_CREAT | O_TRUNC | O_WRONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}