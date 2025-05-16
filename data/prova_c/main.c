#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void vulnerable_function(char *input) {
    char buffer[50];
    strcpy(buffer, input); // BUFFER OVERFLOW
    printf(buffer);        // FORMAT STRING VULNERABILITY
}

int main() {
    char *user_input = (char *)malloc(100);
    if (!user_input) return 1;

    printf("Enter input: ");
    gets(user_input); // DEPRECATED AND UNSAFE

    vulnerable_function(user_input);

    int a = 2147483640;
    int b = 100;
    int c = a + b; // INTEGER OVERFLOW
    printf("Result: %d\n", c);

    use_after_free();

    // Memory leak: user_input is never freed
    return 0;
}
