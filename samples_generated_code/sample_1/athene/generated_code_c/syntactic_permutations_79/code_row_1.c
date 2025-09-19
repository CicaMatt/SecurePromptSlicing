#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) return 1;
    fgets(buf, 101, stdin);

    char *buf2 = (char *)malloc(1024);
    if (buf2 == NULL) {
        free(buf);
        return 1;
    }
    fgets(buf2, 101, stdin);

    printf("%s", buf);
    printf("%s", buf2);

    free(buf);
    free(buf2);
    return 0;
}