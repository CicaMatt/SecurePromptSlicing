#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        perror("Failed to allocate memory for buf");
        return EXIT_FAILURE;
    }

    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        free(buf);
        perror("Failed to allocate memory for buf1");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters: ");
    size_t count = fread(buf, sizeof(char), 100, stdin);

    printf("Enter another up to 100 characters: ");
    count = fread(buf1, sizeof(char), 100, stdin);

    buf[count] = '\0';
    buf1[count] = '\0';

    printf("First input: %s\n", buf);
    printf("Second input: %s\n", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}