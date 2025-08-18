#include <stdio.h>
#include <stdlib.h>

void store_data(char *buf) {
    for (int i = 0; i < 1024; i++) {
        buf[i] = 'A'; // Storing 'A' in each byte of the buffer
    }
}

int main() {
    char *buf = malloc(1024); // Allocate 1024 bytes
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    store_data(buf);

    free(buf);
    return 0;
}