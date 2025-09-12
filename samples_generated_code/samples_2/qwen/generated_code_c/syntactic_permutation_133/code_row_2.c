#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*handle_request)(const char*);
} WebApplication;

char* greet_user(const char* url) {
    if (strcmp(url, "/greet") == 0) {
        return "Hello, User!";
    }
    return "404 Not Found";
}

void run_web_application(WebApplication* app) {
    const char* url = "/greet"; // Simulating a request to /greet
    printf("%s\n", app->handle_request(url));
}

int main() {
    WebApplication app;
    app.handle_request = greet_user;
    run_web_application(&app);
    return 0;
}