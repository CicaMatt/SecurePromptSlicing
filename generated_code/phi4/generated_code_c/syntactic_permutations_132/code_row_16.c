#include <stdio.h>
#include <string.h>

void hello(const char* username) {
    printf("Hello, %s!\n", username);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/<username>\n", argv[0]);
        return 1;
    }

    const char* url = argv[1];
    const char* username_start = url + strlen("/hello/");
    
    if (*username_start == '\0') {
        printf("Error: No username provided.\n");
        return 1;
    }
    
    hello(username_start);
    return 0;
}