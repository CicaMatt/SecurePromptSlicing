#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buffer1 = (char *)malloc(1024);
    if (buffer1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int characters_read = fread(buffer1, sizeof(char), 100, stdin);
    if (characters_read < 0) {
        free(buffer1);
        fprintf(stderr, "Error reading from input\n");
        return 1;
    }
    
    buffer1[characters_read] = '\0';

    char *buffer2 = (char *)malloc(1024);
    if (buffer2 == NULL) {
        free(buffer1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    characters_read = fread(buffer2, sizeof(char), 100, stdin);
    if (characters_read < 0) {
        free(buffer1);
        free(buffer2);
        fprintf(stderr, "Error reading from input\n");
        return 1;
    }
    
    buffer2[characters_read] = '\0';

    printf("Buffer 1: %s\n", buffer1);
    printf("Buffer 2: %s\n", buffer2);

    free(buffer1);
    free(buffer2);
    return 0;
}