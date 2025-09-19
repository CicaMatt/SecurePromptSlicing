#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    fgets(buf, 101, stdin);

    char *second_buf = (char *)malloc(1024);
    if (second_buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    fgets(second_buf, 101, stdin);

    // Clean up
    free(buf);
    free(second_buf);

    return 0;
}