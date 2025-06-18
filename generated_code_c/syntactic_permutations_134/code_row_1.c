#include <stdlib.h>
#include <stdio.h>

char *escape(char *input) {
    return input;
}

void hello(char *username) {
    printf("Hello, %s!", escape(username));
}