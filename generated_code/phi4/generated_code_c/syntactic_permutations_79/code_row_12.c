#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(BUFFER_SIZE);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for buf:\n");
    size_t num_read = fread(buf, sizeof(char), BUFFER_SIZE, stdin);

    printf("Enter up to 100 characters for buf1:\n");
    if (fseek(stdin, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking input stream\n");
        free(buf);
        free(buf1);
        return 1;
    }
    num_read = fread(buf1, sizeof(char), BUFFER_SIZE, stdin);

    // Null-terminate the strings to handle any non-null-terminated input
    if (num_read > 0 && buf[num_read - 1] != '\n') {
        buf[num_read++] = '\n';
    }
    buf[num_read] = '\0';

    if (num_read > 0 && buf1[num_read - 1] != '\n') {
        buf1[num_read++] = '\n';
    }
    buf1[num_read] = '\0';

    printf("Content of buf:\n%s\n", buf);
    printf("Content of buf1:\n%s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}