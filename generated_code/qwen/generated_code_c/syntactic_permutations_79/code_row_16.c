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

    fgets(buf, 1024, stdin);
    buf[strcspn(buf, "\n")] = '\0'; // Remove newline character

    fgets(buf1, 1024, stdin);
    buf1[strcspn(buf1, "\n")] = '\0'; // Remove newline character

    free(buf);
    free(buf1);

    return 0;
}