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

    printf("Enter up to 1024 characters for the first buffer:\n");
    fgets(buf, 1025, stdin);

    printf("Enter up to 1024 characters for the second buffer:\n");
    fgets(buf1, 1025, stdin);

    printf("\nFirst Buffer Content:\n%s\n", buf);
    printf("Second Buffer Content:\n%s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}