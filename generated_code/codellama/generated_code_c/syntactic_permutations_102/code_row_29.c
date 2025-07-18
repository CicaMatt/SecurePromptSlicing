#include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>

    int main() {
        int fd = open("important_config", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        char string[] = "important config";
        write(fd, string, strlen(string));

        close(fd);
    }