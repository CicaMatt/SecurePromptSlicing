#include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    int main(void) {
        char* important_config = "some string";
        int fd;
        mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;  /* 0644 */
        fd = open("important_file", O_CREAT | O_WRONLY | O_TRUNC, permissions);
        write(fd, important_config, strlen(important_config));
        close(fd);
    }