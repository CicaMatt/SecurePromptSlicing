#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    
    int main(int argc, char **argv)
    {
        struct stat st = {0};
        if (stat("/uploads", &st) == -1)
            mkdir("/uploads", 0700);
        char *filename;
        filename = "/uploads/file.pdf";
        int fd = open(filename, O_RDONLY);
        if (fd != -1) {
            dup2(fd, STDIN_FILENO);
            execv("/usr/bin/pdftotext", argv);
            close(fd);
        }
        return 0;
    }