#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(10 * sizeof(char));
    if (buf == NULL) {
        exit(EXIT_FAILURE);
    }
    fgets(buf, 10, stdin);
    printf("%s", buf);
    free(buf);
    return 0;
}