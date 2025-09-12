#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        exit(1);
    }
    return buf;
}

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buf = allocate_buffer();
    read_input(buf);
    printf("Input: %s", buf);
    free(buf);
    return 0;
}