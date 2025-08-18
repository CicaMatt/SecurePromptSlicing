#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return 1;
    }

    printf("Enter up to 100 characters for buf:\n");
    size_t bytesRead = fread(buf, 1, 100, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed for buf1\n");
        free(buf); // Free previously allocated memory
        return 1;
    }

    printf("Enter up to 100 characters for buf1:\n");
    bytesRead = fread(buf1, 1, 100, stdin);

    printf("\nCharacters stored in buf:\n%s\n", buf);
    printf("Characters stored in buf1:\n%s\n", buf1);

    free(buf);
    free(buf1);
    
    return 0;
}