#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>

    void img(char *name) {
        FILE *fp = fopen("images/" name, "r");
        if (!fp) {
            perror("fopen() failed!");
            return;
        }
        char buf[1024];
        size_t nread;
        while ((nread = fread(buf, 1, sizeof buf, fp)) > 0) {
            printf("%s", buf);
        }
        if (ferror(fp)) {
            perror("fread() failed!");
        }
    }

    void decorator() {
        img();
        return 0;
    }