#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 11

void allocate_and_read() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    printf("Enter up to 10 characters: ");
    if (fgets(buf, BUFFER_SIZE, stdin) != NULL) {
        buf[strcspn(buf, "\n")] = '\0'; // Remove newline character if present
    } else {
        free(buf);
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }

    printf("You entered: %s\n", buf);

    free(buf);
}

int main() {
    allocate_and_read();
    return 0;
}