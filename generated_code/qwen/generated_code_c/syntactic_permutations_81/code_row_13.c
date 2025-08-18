#include <stdio.h>
#include <stdlib.h>

void read_characters(char *buf) {
    printf("Enter 10 characters: ");
    for (int i = 0; i < 10; i++) {
        scanf("%c", &buf[i]);
    }
}

int main() {
    char *buffer = (char *)malloc(1024 * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    read_characters(buffer);

    printf("You entered: ");
    for (int i = 0; i < 10; i++) {
        putchar(buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}