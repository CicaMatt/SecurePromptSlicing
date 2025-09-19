#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} Request;

typedef struct {
    const char *path;
    void (*handler)(Request*);
} Route;

void render_template(const char *template, const char *username) {
    printf("Template: %s\n", template);
    printf("Welcome, %s!\n", username);
}

void hello(Request *req) {
    const char *template = "<html><body>Welcome, {{username}}!</body></html>";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), template, req->username);
    render_template(buffer, req->username);
}

void route_handler(Route *route, Request *req) {
    if (strcmp(route->path, "/hello/") == 0) {
        route->handler(req);
    }
}

int main() {
    Route routes[] = {{"^/hello/(.*)$", hello}, {NULL, NULL}};
    
    char username[50];
    printf("Enter username: ");
    scanf("%s", username);

    Request req = {.username = username};
    route_handler(&routes[0], &req);
    
    return 0;
}