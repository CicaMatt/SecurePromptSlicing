#include <stdio.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    int main() {
        char *filename = "important_config";
        if (access(filename, F_OK) == 0) {
            printf("File already exists\n");
            return 1;
        }
        umask(0);
        int fd = open(filename, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            perror("open");
            return 1;
        }
        printf("File created\n");
        close(fd);
        return 0;
    }