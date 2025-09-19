#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
    char buffer[BUFFER_SIZE];

    memset(buffer, 'A', sizeof(buffer));

    for (size_t i = 0; i < sizeof(buffer); ++i) {
        printf("%c", buffer[i]);
    }

    printf("\n");

    return 0;
}