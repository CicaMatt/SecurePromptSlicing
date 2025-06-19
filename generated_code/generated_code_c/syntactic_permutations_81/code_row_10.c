#include <stdio.h>
    #include <string.h> // for memcpy
    #include <stdlib.h> // for malloc
    #define BUF_SIZE 1024

    void loadData(char *buf) {
        char data[BUF_SIZE] = "Hello World";
        memcpy(buf, data, BUF_SIZE);
    }

    int main() {
        char *buf = (char *)malloc(BUF_SIZE);
        loadData(buf);
        printf("buf: %s\n", buf);
        return 0;
    }