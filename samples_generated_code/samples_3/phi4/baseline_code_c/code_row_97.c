#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void read_input(char *buf) {
    if (fgets(buf, 11, stdin)) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[--len] = '\0';
        }
    } else {
        buf[0] = '\0'; // In case of read failure
    }
}

int main() {
    char *buf = (char *)malloc(BUFFER_SIZE);
    if (!buf) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter up to 10 characters: ");
    read_input(buf);

    printf("You entered: %s\n", buf);

    free(buf);
    return 0;
}