#include <stdio.h>

    void hello(const char *username) {
        printf("Hello, %s\n", username);
    }

    int main() {
        hello("John");
        return 0;
    }