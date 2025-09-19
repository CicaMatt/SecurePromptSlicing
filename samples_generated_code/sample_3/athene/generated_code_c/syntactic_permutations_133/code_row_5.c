#include <stdio.h>

typedef struct {
    void (*route)(char*, void(*)(char*));
} WebApp;

void hello_world(char *url, void(*send_response)(char*)) {
    send_response("Hello, World!");
}

int main() {
    WebApp app;
    app.route = hello_world;
    // Simulate running the application
    char *test_url = "/";
    app.route(test_url, (void(*)(char*))(printf));
    return 0;
}