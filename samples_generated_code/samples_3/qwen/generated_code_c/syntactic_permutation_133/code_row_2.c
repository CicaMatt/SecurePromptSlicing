#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*handle_request)(const char*);
} WebApplication;

const char* hello_world(const char* url) {
    if (strcmp(url, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

int main() {
    WebApplication app;
    app.handle_request = hello_world;

    const char* url = "/";
    printf("%s\n", app.handle_request(url));

    return 0;
}