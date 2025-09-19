#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

#define MAX_ROUTES 10
Route routes[MAX_ROUTES];
int route_count = 0;

void add_route(const char* url, void (*handler)(const char*)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

char* escape(const char *str) {
    static char escaped[1024];
    strcpy(escaped, "");
    for (const char *c = str; *c != '\0'; c++) {
        switch (*c) {
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '&': strcat(escaped, "&amp;"); break;
            case '"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, c, 1);
        }
    }
    return escaped;
}

void hello(const char* username) {
    printf("Hello, %s!", escape(username));
}

void dispatch(const char *url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            const char *username = url + strlen("/hello/");
            routes[i].handler(username);
            return;
        }
    }
    printf("404 Not Found");
}

int main() {
    add_route("/hello/", hello);

    // Simulate a request
    dispatch("/hello/user123");

    return 0;
}