#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 1024 characters: ");
    if (fgets(buf, 1025, stdin) != NULL) {
        strncpy(buf1, buf, sizeof(buf));
        buf1[strcspn(buf1, "\n")] = '\0'; // Remove trailing newline if present
    } else {
        fprintf(stderr, "Error reading input\n");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("First buffer: %s\n", buf);
    printf("Second buffer: %s\n", buf1);

    free(buf);
    free(buf1);
    return 0;
}