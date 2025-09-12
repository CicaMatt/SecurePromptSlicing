#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *username);
} Route;

void escape(char *dest, const char *src) {
    while (*src) {
        switch (*src) {
            case '<': strcpy(dest, "&lt;"); dest += 4; break;
            case '>': strcpy(dest, "&gt;"); dest += 4; break;
            case '&': strcpy(dest, "&amp;"); dest += 5; break;
            case '"': strcpy(dest, "&quot;"); dest += 6; break;
            default: *dest = *src; dest++; break;
        }
        src++;
    }
    *dest = '\0';
}

void hello(const char *username) {
    char escaped_username[1024];
    escape(escaped_username, username);
    printf("Hello %s\n", escaped_username);
}

typedef void (*RouteHandler)(const char *);

void route(Route routes[], int count, const char *url, const char *username) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {
        {"/hello/", hello}
    };
    int route_count = sizeof(routes) / sizeof(Route);

    const char *url = "/hello/";
    const char *username = "user123";

    route(routes, route_count, url, username);
    return 0;
}