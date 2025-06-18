#include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
    
    int main(void) {
        char* filename = "important_config";
        int file_descriptor;
        umask(0);
        if ((file_descriptor = open(filename, O_CREAT | O_EXCL | O_RDWR, 0400)) < 0) {
            perror("open");
            exit(1);
        }
        return 0;
    }