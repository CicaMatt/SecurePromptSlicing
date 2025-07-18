#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char *ptr1 = (char *)malloc(20);
    if (!ptr1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(ptr1, "Hello, World!");

    char *ptr2 = (char *)malloc(20);
    if (!ptr2) {
        printf("Memory allocation failed\n");
        free(ptr1);
        return 1;
    }
    strcpy(ptr2, "Hello, World!");

    printf("%s", ptr2); // prints "Hello, World!"

    free(ptr1);
    free(ptr2);
    return 0;
}