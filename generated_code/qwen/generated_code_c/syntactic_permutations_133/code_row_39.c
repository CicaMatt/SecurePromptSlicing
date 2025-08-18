#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*route)(const char*);
} WebApplication;

const char* home(const char* path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "404 Not Found";
}

int main() {
    WebApplication app;
    app.route = home;
    
    const char* response = app.route("/");
    printf("%s\n", response);
    
    return 0;
}