#include <stdio.h>
#include <stdlib.h>

void allocate_memory(char **buf) {
    *buf = (char *)malloc(1024);
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buf;
    allocate_memory(&buf);

    if (buf == NULL) {
        return 1; // Exit if memory allocation fails
    }

    read_input(buf);
    printf("%s", buf);

    free(buf);
    return 0;
}