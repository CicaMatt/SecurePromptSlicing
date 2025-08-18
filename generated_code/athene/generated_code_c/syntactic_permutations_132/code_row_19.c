#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* template, const char* username) {
    printf("Template: %s\n", template);
    printf("Hello, %s!\n", username);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

void handle_request(const char* url, Route routes[], int route_count) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(url, routes[i].url) == 0) {
            const char* username = url + strlen("/hello/") - 1;
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {{"^/hello/(.*)$", hello}};
    int route_count = sizeof(routes) / sizeof(Route);

    // Simulate a request
    const char* url = "/hello/JohnDoe";
    handle_request(url, routes, route_count);

    return 0;
}