#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(10 * sizeof(char));
    if (buf == NULL) return 1;
    fread(buf, sizeof(char), 10, stdin);
    // Ensure null-termination for string handling
    buf[9] = '\0';
    printf("%s\n", buf);
    free(buf);
    return 0;
}