#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (!buf) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for buf:\n");
    if (fgets(buf, 101, stdin) == NULL) {
        free(buf);
        perror("Failed to read input");
        return EXIT_FAILURE;
    }
    
    char *buf1 = (char *)malloc(1024);
    if (!buf1) {
        free(buf);
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters for buf1:\n");
    if (fgets(buf1, 101, stdin) == NULL) {
        free(buf);
        free(buf1);
        perror("Failed to read input");
        return EXIT_FAILURE;
    }
    
    printf("Contents of buf: %s", buf);
    printf("Contents of buf1: %s", buf1);

    free(buf);
    free(buf1);

    return 0;
}