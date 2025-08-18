#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Enter up to 100 characters for the first buffer:\n");
    if (fgets(buf, 101, stdin) == NULL) {
        free(buf);
        perror("Failed to read input");
        return 1;
    }
    
    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        perror("Failed to allocate memory");
        free(buf);
        return 1;
    }

    printf("Enter up to 100 characters for the second buffer:\n");
    if (fgets(buf1, 101, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Failed to read input");
        return 1;
    }
    
    printf("First Buffer: %s", buf);
    printf("Second Buffer: %s", buf1);

    free(buf);
    free(buf1);
    return 0;
}