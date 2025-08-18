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

    fgets(buf, 101, stdin);
    buf[strcspn(buf, "\n")] = '\0';

    fgets(buf1, 101, stdin);
    buf1[strcspn(buf1, "\n")] = '\0';

    free(buf);
    free(buf1);

    return 0;
}