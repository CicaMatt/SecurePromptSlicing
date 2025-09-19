#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus null terminator
    buf[10] = '\0'; // Ensure null termination
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        return 1;
    }

    read_input(buf);

    printf("Input: %s", buf);

    free(buf);
    return 0;
}