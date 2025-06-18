#include <stdio.h>
    #include <stdlib.h>

    int main(){
        char *buf = malloc(1024);
        fread(buf, 10, 1, stdin);
        return 0;
    }