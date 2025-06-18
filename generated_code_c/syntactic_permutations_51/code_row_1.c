#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <tarfile.h>

int main(void){
    char *dirname = "/tmp/unpack";
    mkdir(dirname, 0755);
    chdir(dirname);
    int fd;
    if ((fd = open("test.tar", O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    tarfile_t *tf;
    if (!(tf = tarfile_openfd(fd, O_RDONLY))) {
        fprintf(stderr, "tarfile_open: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char *filename;
    while ((filename = tarfile_next(tf)) != NULL) {
        if (tarfile_extract(tf, filename) == -1) {
            fprintf(stderr, "tarfile_extract: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    tarfile_close(tf);
    close(fd);
    return 0;
}