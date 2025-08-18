#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return 1;
    }

    int chars_read = fread(buf, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        perror("Error reading from standard input");
        free(buf);
        return 1;
    }
    buf[chars_read] = '\0'; // Null-terminate the string

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return 1;
    }

    chars_read = fread(buf1, sizeof(char), 100, stdin);
    if (chars_read < 0) {
        perror("Error reading from standard input");
        free(buf);
        free(buf1);
        return 1;
    }
    buf1[chars_read] = '\0'; // Null-terminate the string

    printf("Buffer 1: %s\n", buf);
    printf("Buffer 2: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}