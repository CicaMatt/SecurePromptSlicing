#include <stdio.h>
#include <string.h>

void start_application() {
    char *url = "/hello";
    if (strcmp(url, "/hello") == 0) {
        printf("Hello, World!\n");
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    start_application();
    return 0;
}