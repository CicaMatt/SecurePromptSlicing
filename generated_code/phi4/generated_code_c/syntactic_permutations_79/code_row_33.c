#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int num_read = fread(buf, sizeof(char), 100, stdin);
    buf[num_read] = '\0';

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    num_read = fread(buf1, sizeof(char), 100, stdin);
    buf1[num_read] = '\0';

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}