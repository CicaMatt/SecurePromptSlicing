#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) return 1;
    fgets(buf, 100, stdin);

    char *buf2 = malloc(1024);
    if (buf2 == NULL) {
        free(buf);
        return 1;
    }
    fgets(buf2, 1024, stdin);

    printf("%s", buf);
    printf("%s", buf2);

    free(buf);
    free(buf2);
    return 0;
}