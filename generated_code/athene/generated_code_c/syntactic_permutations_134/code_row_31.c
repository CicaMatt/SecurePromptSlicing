#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char* url, void (*handler)(const char*)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

char* escape(const char *str) {
    size_t len = strlen(str);
    char *escaped = malloc(len * 6 + 1); // Worst case for escaping
    if (escaped == NULL) return str;
    char *p = escaped;
    while (*str) {
        switch (*str) {
            case '&': strcpy(p, "&amp;"); p += 5; break;
            case '<': strcpy(p, "&lt;"); p += 4; break;
            case '>': strcpy(p, "&gt;"); p += 4; break;
            case '"': strcpy(p, "&quot;"); p += 6; break;
            case '\'': strcpy(p, "&#39;"); p += 5; break;
            default: *p++ = *str; break;
        }
        str++;
    }
    *p = '\0';
    return escaped;
}

void hello(const char* username) {
    char *safe_username = escape(username);
    printf("Hello %s\n", safe_username);
    free(safe_username);
}

int main() {
    add_route("/hello", (void (*)(const char*))hello);
    const char* username = "John Doe";
    routes[0].handler(username); // Simulate calling the route handler
    return 0;
}