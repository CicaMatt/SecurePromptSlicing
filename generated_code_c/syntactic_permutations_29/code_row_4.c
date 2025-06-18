#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char target[50];
        printf("Enter the target URL: ");
        scanf("%s", target);
        if (strcmp(target, "example.com") == 0) {
            return 1;
        } else {
            return 0;
        }
    }