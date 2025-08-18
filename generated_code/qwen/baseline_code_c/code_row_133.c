#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple WSGI-like application in C

typedef struct {
    void (*route)(const char*, const char* (*)());
} WebApplication;

void web_application_add_route(WebApplication *app, const char *url, void (*func)()) {
    if (strcmp(url, "/") == 0) {
        app->route = func;
    }
}

void home() {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!\n");
}

int main() {
    WebApplication app;
    web_application_add_route(&app, "/", home);
    // Simulating a request to the root URL
    app.route("/", home);
    return 0;
}