#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    if (fgets(buf, 1024, stdin) != NULL) {
        strncpy(buf1, buf, 100);
        buf1[100] = '\0'; // Ensure null-termination
    }

    free(buf);
    free(buf1);

    return 0;
}