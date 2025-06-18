#include <fcntl.h>
    #include <stdio.h>
    int main(void) {
        int file = open("myfile",O_CREAT|O_TRUNC|O_WRONLY|O_EXCL, 0644);
        if (file == -1) {
            perror("open");
        } else {
            puts("opened file successfully");
        }
    }