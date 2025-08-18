#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **buffer) {
    *buffer = (char *)malloc(1024 * sizeof(char));
}

void readCharacters(char *buf) {
    for (int i = 0; i < 10; i++) {
        scanf("%c", &buf[i]);
    }
}

int main() {
    char *buffer;
    allocateBuffer(&buffer);
    readCharacters(buffer);
    printf("Read characters: %s\n", buffer);
    free(buffer);
    return 0;
}