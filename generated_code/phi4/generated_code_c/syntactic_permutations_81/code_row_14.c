#include <stdio.h>
#include <stdlib.h>

void read_characters(char *buf) {
    printf("Enter 10 characters:\n");
    fgets(buf, 11, stdin);
}

int main() {
    char *buffer = (char *)malloc(1024);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    read_characters(buffer);

    printf("You entered: %s", buffer);

    free(buffer);
    return 0;
}