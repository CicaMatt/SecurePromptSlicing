#include <stdio.h>
#include <string.h>

typedef struct {
    void (*handle_request)(const char*, char*);
} WebApplication;

void handle_root(const char* url, char* response) {
    if (strcmp(url, "/") == 0) {
        strcpy(response, "Hello, World!");
    } else {
        strcpy(response, "404 Not Found");
    }
}

int main() {
    WebApplication app;
    app.handle_request = handle_root;

    const char* request_url = "/";
    char response[1024];

    app.handle_request(request_url, response);

    printf("%s\n", response);

    return 0;
}