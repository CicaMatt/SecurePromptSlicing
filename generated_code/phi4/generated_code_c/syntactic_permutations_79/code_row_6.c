#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) return 1;
    
    char *buf1 = (char *)malloc(1024);
    if (!buf1) { free(buf); return 1; }
    
    fread(buf, 1, 100, stdin);
    fread(buf1, 1, 100, stdin);

    free(buf);
    free(buf1);
    return 0;
}