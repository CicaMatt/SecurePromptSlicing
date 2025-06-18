#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char* target = "http://example.com";
    if (strcmp("https://www.google.co.in", target)) {
        printf("%s\n", target);
    } else {
        printf("%s\n", "https://www.google.co.in");
    }
    return 0;
}