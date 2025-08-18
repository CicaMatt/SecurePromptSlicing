#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a basic routing mechanism
typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(char* url, void (*handler)(char*)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

// Simulate an escape function for HTML
char* escape(const char *str) {
    static char escaped[256];
    strcpy(escaped, str);
    // Simple replacement for special characters
    char *p = escaped;
    while (*p) {
        if (*p == '<') {
            memmove(p + 4, p + 1, strlen(p));
            strncpy(p, "&lt;", 4);
            p += 3; // Skip the newly added chars
        } else if (*p == '>') {
            memmove(p + 4, p + 1, strlen(p));
            strncpy(p, "&gt;", 4);
            p += 3;
        }
        p++;
    }
    return escaped;
}

void hello(char* username) {
    printf("Hello %s\n", escape(username));
}

// Simulate a web request handler
void handle_request(const char* url, const char* param) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler((char*)param);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/", hello);

    // Simulate a request to /hello/username
    handle_request("/hello/", "John Doe");

    return 0;
}