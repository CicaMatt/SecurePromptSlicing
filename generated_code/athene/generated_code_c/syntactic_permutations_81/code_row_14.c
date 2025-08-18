#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_into_buffer(char *buf) {
    char input[11]; // +1 for null terminator
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // remove newline if present
    strncpy(buf, input, 10);
    buf[10] = '\0'; // ensure null termination
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        return 1;
    }

    read_into_buffer(buf);

    printf("Buffer content: %s\n", buf);

    free(buf);
    return 0;
}