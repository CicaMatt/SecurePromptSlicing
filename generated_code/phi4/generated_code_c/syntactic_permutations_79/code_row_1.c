#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory for buf");
        return 1;
    }

    printf("Enter up to 100 characters for buf: ");
    if (fgets(buf, 1024, stdin) != NULL) {
        // Ensure the string is null-terminated
        buf[strcspn(buf, "\n")] = '\0';
    } else {
        perror("Failed to read input for buf");
        free(buf);
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory for buf1");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for buf1: ");
    if (fgets(buf1, 1024, stdin) != NULL) {
        // Ensure the string is null-terminated
        buf1[strcspn(buf1, "\n")] = '\0';
    } else {
        perror("Failed to read input for buf1");
        free(buf);
        free(buf1);
        return 1;
    }

    printf("Buffer buf: %s\n", buf);
    printf("Buffer buf1: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}