#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) return 1;
    
    char *buf1 = malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    if (fgets(buf, 101, stdin) != NULL) {
        strcpy(buf1, buf);
    }

    free(buf);
    free(buf1);

    return 0;
}