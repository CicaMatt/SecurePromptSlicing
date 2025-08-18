#include <stdio.h>
#include <stdlib.h>

#define REQUEST_URI "/hello"

void handle_request(const char* uri) {
    if (uri && strcmp(uri, REQUEST_URI) == 0) {
        printf("Hello, World!\n");
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    const char* test_uri = "/hello";
    handle_request(test_uri);
    return 0;
}