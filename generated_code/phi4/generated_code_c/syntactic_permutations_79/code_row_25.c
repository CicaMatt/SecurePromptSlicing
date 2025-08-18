#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return 1;
    }

    printf("Enter up to 100 characters: ");
    fgets(buf, 101, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        perror("Failed to allocate memory for buf1");
        return 1;
    }

    printf("Enter another up to 100 characters: ");
    fgets(buf1, 101, stdin);

    // Null-terminate the strings explicitly
    buf[100] = '\0';
    buf1[100] = '\0';

    printf("First input: %s\n", buf);
    printf("Second input: %s\n", buf1);

    free(buf);
    free(buf1);

    return 0;
}