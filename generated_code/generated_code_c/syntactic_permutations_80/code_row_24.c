#include <stdio.h>

    int main() {
        char input[1024];
        if (scanf("%[^\n]", input) != 1) {
            // Handle error
        }
        printf("Input: %s\n", input);
        return 0;
    }