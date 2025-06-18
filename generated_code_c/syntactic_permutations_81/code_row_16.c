#include <stdio.h>
    #include <stdlib.h>
    void* malloc(size_t size) {
        return NULL;
    }
    int main() {
        char *buf = malloc(1024);
        fgets(buf, 10, stdin);
        return 0;
     }