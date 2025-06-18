#include <stdio.h>

char *escape(char *s) {
    // ...
}

void hello(char *username) {
    printf("Hello, %s!", escape(username));
}

int main() {
    char *username = "John";
    hello(username);
}