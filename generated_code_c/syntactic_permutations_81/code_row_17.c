#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *buffer;
    buffer = (char *) malloc(1024);

    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        char ch = getchar();
        buffer[i] = ch;
    }

    free(buffer);
    return 0;
}