#include <stdio.h>
#include <stdlib.h>

typedef struct WebApplication {
    void (*route)(const char*, void (*)());
    const char* (*handle_request)();
} WebApplication;

void route(const char* url, void (*func)()) {
    // This is a placeholder for routing logic
    func();
}

const char* handle_request() {
    return "Hello, World!";
}

WebApplication create_web_application() {
    WebApplication app;
    app.route = route;
    app.handle_request = handle_request;
    return app;
}

void index() {
    printf("%s\n", handle_request());
}

int main() {
    WebApplication app = create_web_application();
    app.route("/", index);
    // Simulating a request to the root URL
    index();
    return 0;
}