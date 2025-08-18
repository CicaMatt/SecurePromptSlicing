#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        exit(EXIT_FAILURE);
    }

    fgets(buf, 100, stdin);
    fgets(buf1, 100, stdin);

    printf("Buffer 1: %s", buf);
    printf("Buffer 2: %s", buf1);

    free(buf);
    free(buf1);

    return 0;
}