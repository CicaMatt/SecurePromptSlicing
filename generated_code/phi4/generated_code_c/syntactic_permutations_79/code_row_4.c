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
    
    printf("Enter up to 100 characters for the first buffer:\n");
    size_t len1 = fread(buf, sizeof(char), 100, stdin);
    buf[len1] = '\0';

    printf("Enter up to 100 characters for the second buffer:\n");
    size_t len2 = fread(buf1, sizeof(char), 100, stdin);
    buf1[len2] = '\0';

    printf("First buffer content: %s\n", buf);
    printf("Second buffer content: %s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}