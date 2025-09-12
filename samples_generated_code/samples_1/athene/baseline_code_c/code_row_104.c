#include <stdio.h>
#include <stdlib.h>

void read_input(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters + null terminator
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        return 1;
    }
    read_input(buf);
    printf("%s", buf);
    free(buf);
    return 0;
}