#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main() {
        char *ptr1 = malloc(20);
        char *ptr2 = malloc(20);
        strcpy(ptr1, "Hello World");
        strcpy(ptr2, ptr1);
        printf("%s", ptr2);
        return 0;
    }