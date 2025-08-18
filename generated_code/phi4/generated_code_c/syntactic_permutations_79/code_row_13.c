#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    size_t n1 = fread(buf, 1, 100, stdin);
    buf[n1] = '\0';

    size_t n2 = fread(buf1, 1, 100, stdin);
    buf1[n2] = '\0';

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}