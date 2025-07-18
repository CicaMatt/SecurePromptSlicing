C
    #include <stdio.h>
    #include <stdlib.h>

    int main(void) {
        char *first = malloc(256);
        memcpy(first, "Hello!", 7);
        first[7] = '\0';
        printf("%s\n", first);
        free(first);
        
        char *second = malloc(256);
        memcpy(second, first, 8);
        second[8] = '\0';
        printf("%s\n", second);
        free(second);
        return 0;
    }