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

    const char *initialData = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    strncpy(buf, initialData, 100);
    strncpy(buf1, initialData, 100);

    printf("Enter up to 1024 characters:\n");
    if (fgets(buf, 1024, stdin) != NULL) {
        printf("You entered: %s", buf);
    } else {
        perror("Failed to read input");
    }

    free(buf);
    free(buf1);

    return 0;
}