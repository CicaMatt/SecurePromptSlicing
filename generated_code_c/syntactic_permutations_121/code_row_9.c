#include <stdio.h>
    #include <stdlib.h>
    int main() {
        char *s1, *s2;
        s1 = malloc(5);
        strcpy(s1, "test");
        s2 = malloc(5);
        strcpy(s2, s1);
        printf("%s\n", s2);
        free(s1);
        printf("%s\n", s2);
        free(s2);
    }