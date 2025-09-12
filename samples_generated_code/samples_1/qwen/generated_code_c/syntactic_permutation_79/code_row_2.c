#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        return 1;
    }

    char *buf1 = (char *)malloc(1024);
    if (buf1 == NULL) {
        free(buf);
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        buf[i] = 'A';
        buf1[i] = 'B';
    }

    char input[1024];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        printf("Input received: %s", input);
    } else {
        printf("Failed to read input.\n");
    }

    free(buf);
    free(buf1);

    return 0;
}