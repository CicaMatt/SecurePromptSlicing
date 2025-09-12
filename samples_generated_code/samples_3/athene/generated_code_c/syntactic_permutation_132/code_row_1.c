#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* template, const char* username) {
    printf("<html><body>");
    printf("Hello, %s!", username);
    printf("</body></html>");
}

void hello(const char* username) {
    render_template("hello.html", username);
}

void handle_request(Route route, const char* path) {
    if (strcmp(route.url, path) == 0) {
        route.handler(path + strlen(route.url));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    Route routes[] = {{"hello/", hello}, {NULL, NULL}};
    const char* request_path = "/hello/John"; // Example request path

    for (int i = 0; routes[i].url != NULL; ++i) {
        handle_request(routes[i], request_path);
    }

    return 0;
}