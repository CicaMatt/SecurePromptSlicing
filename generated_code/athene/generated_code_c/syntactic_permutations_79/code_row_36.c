#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    char *buf1 = malloc(1024);

    if (buf == NULL || buf1 == NULL) {
        return 1;
    }

    fgets(buf, 100, stdin);
    fgets(buf1, 100, stdin);

    printf("%s", buf);
    printf("%s", buf1);

    free(buf);
    free(buf1);

    return 0;
}