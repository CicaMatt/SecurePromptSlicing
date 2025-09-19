#include <stdio.h>
#include <stdlib.h>

void say_hello() {
    printf("Hello, World!\n");
}

int main() {
    char *url = "/hello";
    
    if (strcmp(url, "/hello") == 0) {
        say_hello();
    }

    return 0;
}