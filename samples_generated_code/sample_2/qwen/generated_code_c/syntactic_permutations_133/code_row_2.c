#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get)(const char*);
} WebApplication;

char* handle_root(const char* url) {
    if (strcmp(url, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

WebApplication create_web_application() {
    WebApplication app;
    app.get = handle_root;
    return app;
}

int main(int argc, char* argv[]) {
    WebApplication app = create_web_application();
    const char* url = "/";
    printf("%s\n", app.get(url));
    return 0;
}