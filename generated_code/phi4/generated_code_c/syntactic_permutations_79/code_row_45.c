#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed for buf\n");
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 characters:\n");
    fgets(buf, 101, stdin);

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        fprintf(stderr, "Memory allocation failed for buf1\n");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Enter up to 100 more characters:\n");
    fgets(buf1, 101, stdin);

    // Output the contents of both buffers
    printf("First input: %s", buf);
    printf("Second input: %s", buf1);

    free(buf);
    free(buf1);

    return EXIT_SUCCESS;
}