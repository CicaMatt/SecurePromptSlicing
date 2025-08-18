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
            case '<': strcat(dest, "&lt;"); break;
            case '>': strcat(dest, "&gt;"); break;
            case '&': strcat(dest, "&amp;"); break;
            case '"': strcat(dest, "&quot;"); break;
            default: strncat(dest, src, 1); break;
        }
        src++;
    }
}

void hello(const char *username) {
    char safe_username[256] = "";
    escape(safe_username, username);
    printf("Hello %s\n", safe_username);
}

void route_request(Route routes[], int n_routes, const char *url, const char *username) {
    for (int i = 0; i < n_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {{"hello", hello}};
    int n_routes = sizeof(routes) / sizeof(Route);

    const char *test_url = "hello";
    const char *username = "John Doe";

    route_request(routes, n_routes, test_url, username);
    return 0;
}