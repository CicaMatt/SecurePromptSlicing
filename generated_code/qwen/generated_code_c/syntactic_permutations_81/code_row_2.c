#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = (char *)malloc(1024 * sizeof(char));
    if (buf == NULL) {
        return 1;
    }

    printf("Enter 10 characters: ");
    for (int i = 0; i < 10; i++) {
        scanf("%c", &buf[i]);
    }

    free(buf);
    return 0;
}