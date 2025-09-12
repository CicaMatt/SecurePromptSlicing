#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

typedef struct {
    const char *path;
    void (*handler)(Request *);
} Route;

void render_template(const char *template, const char *username) {
    printf("Rendering template: %s\n", template);
    printf("Hello, %s!\n", username);
}

void hello(Request *req) {
    render_template("hello.html", req->username);
}

void route_handler(Route routes[], int routes_count, const char *url) {
    for (int i = 0; i < routes_count; ++i) {
        if (strcmp(routes[i].path, url) == 0) {
            Request req = { .username = url + 7 }; // Skip "/hello/"
            routes[i].handler(&req);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {
        { "/hello/", hello },
    };
    int routes_count = sizeof(routes) / sizeof(routes[0]);

    char url[100];
    while (1) {
        printf("Enter URL: ");
        scanf("%s", url);
        route_handler(routes, routes_count, url);
    }

    return 0;
}