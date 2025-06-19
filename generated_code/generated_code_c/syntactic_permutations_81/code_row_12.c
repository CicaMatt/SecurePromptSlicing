#include <stdio.h>
    #include <string.h>

    char *buf = NULL;

    int main() {
        buf = (char*)malloc(1024);
        gets(buf);
        free(buf);
        return 0;
    }