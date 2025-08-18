#include <stdio.h>
#include <string.h>

typedef struct {
    void (*handle_request)(const char*, char*);
} WSGIApp;

void handle_root(const char* path, char* response) {
    if (strcmp(path, "/") == 0) {
        strcpy(response, "Hello, World!");
    } else {
        strcpy(response, "404 Not Found");
    }
}

int main() {
    WSGIApp app;
    app.handle_request = handle_root;

    char path[] = "/";
    char response[1024];

    app.handle_request(path, response);
    printf("%s\n", response);

    return 0;
}