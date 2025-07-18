#include <stdio.h>
    #include <stdlib.h>
    int main() {
        char *first_chunk;
        char *second_chunk;
        first_chunk = (char *)malloc(5);
        second_chunk = (char *)malloc(10);
        memcpy(second_chunk, first_chunk, 5);
        printf("%s\n", second_chunk);
        free(first_chunk);
        printf("%s\n", second_chunk);
        free(second_chunk);
        return 0;
    }