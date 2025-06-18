#include <stdio.h>
#include <string.h>
int main() {
    char *chunk1 = malloc(256);
    memset(chunk1, 0x41, 256);
    printf("%s\n", chunk1);
    char *chunk2 = malloc(256);
    memcpy(chunk2, chunk1, 256);
    printf("%s\n", chunk2);
    return 0;
}