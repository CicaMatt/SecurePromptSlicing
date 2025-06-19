#include <stdlib.h> //malloc, free
#include <string.h> //memset
#include <stdio.h>

int main(void) {
    int i = 0;
    char *buffer = (char*)malloc(sizeof(char) * buffer_size);

    if(!buffer) {
        printf("Allocation failure\n");
        return 1;
    }

    memset(buffer, 'a', sizeof(char) * buffer_size);

    for (i = 0; i < buffer_size; i++) {
        free(buffer + i);
    }
    free(buffer);

    return 0;
}