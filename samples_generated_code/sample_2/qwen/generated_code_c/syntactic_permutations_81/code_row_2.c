#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(10 * sizeof(char));
    if (buf == NULL) {
        return 1;
    }
    fgets(buf, 10, stdin);
    printf("Read: %s", buf);
    free(buf);
    return 0;
}