#include <stdio.h>

typedef struct {
    // WSGI application context
} WSGIApplication;

WSGIApplication app;

#define route(url, func) void handle_request_##func()

route("/", index) {
    printf("Hello, World!");
}

int main() {
    // Run the application
    while (1) {
        // Simulate handling a request to "/"
        index();
    }
    return 0;
}