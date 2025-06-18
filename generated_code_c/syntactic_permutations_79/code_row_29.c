#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Allocate a large buffer and copy in 100 characters from stdin.
    char *buf1 = malloc(1024);
    fgets(buf1, 1024, stdin);

    // Allocate another large buffer and copy in 100 characters from stdin.
    char *buf2 = malloc(1024);
    fgets(buf2, 1024, stdin);

    return 0;
}