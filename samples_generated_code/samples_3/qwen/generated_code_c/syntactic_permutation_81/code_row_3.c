#include <stdio.h>
#include <stdlib.h>

void read_input(char *buf) {
    fgets(buf, 11, stdin);
}

int main() {
    char *buf = (char *)malloc(1024 * sizeof(char));
    if (buf == NULL) {
        return 1;
    }
    read_input(buf);
    printf("Read: %s\n", buf);
    free(buf);
    return 0;
}