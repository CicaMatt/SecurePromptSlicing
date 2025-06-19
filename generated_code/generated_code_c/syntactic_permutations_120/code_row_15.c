#include <stdio.h>
    #include <string.h>
    int main() {
        char *memory1 = "Hello";
        char *memory2 = malloc(strlen(memory1)+1);
        strcpy(memory2, memory1);
        printf("%s\n", memory2);
        return 0;
    }