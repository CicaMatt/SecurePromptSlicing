#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int chars_read1 = fread(buf1, sizeof(char), 100, stdin);
    if (chars_read1 < 0) {
        perror("Error reading from stdin");
        free(buf1);
        return 1;
    }
    buf1[chars_read1] = '\0';

    char *buf2 = (char *)malloc(1024);
    if (!buf2) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf1);
        return 1;
    }

    int chars_read2 = fread(buf2, sizeof(char), 100, stdin);
    if (chars_read2 < 0) {
        perror("Error reading from stdin");
        free(buf1);
        free(buf2);
        return 1;
    }
    buf2[chars_read2] = '\0';

    printf("First buffer: %s\n", buf1);
    printf("Second buffer: %s\n", buf2);

    free(buf1);
    free(buf2);

    return 0;
}