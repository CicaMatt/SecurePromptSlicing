#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buffer) {
    *buffer = (char *)malloc(1024);
    if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void readAndStore(int n, char *buf) {
    for (int i = 0; i < n; ++i) {
        printf("Enter a character: ");
        int ch = getchar();
        while (getchar() != '\n'); // Clear input buffer
        buf[i] = (char)ch;
    }
}

int main() {
    char *buf;

    allocateBuffer(&buf);

    printf("Reading and storing 10 characters into the buffer:\n");
    readAndStore(10, buf);

    printf("\nStored Characters:\n");
    for (int i = 0; i < 10; ++i) {
        printf("%c ", buf[i]);
    }
    printf("\n");

    free(buf);
    return 0;
}