#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*func)(const char *);
} Route;

void escape(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&':
                strcat(output, "&amp;");
                break;
            case '<':
                strcat(output, "&lt;");
                break;
            case '>':
                strcat(output, "&gt;");
                break;
            case '"':
                strcat(output, "&quot;");
                break;
            case '\'':
                strcat(output, "&#x27;");
                break;
            default:
                strncat(output, input, 1);
        }
        input++;
    }
}

void hello(const char *username) {
    char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", username);

    char escapedGreeting[512] = "";
    escape(greeting, escapedGreeting);

    printf("%s\n", escapedGreeting);
}

void route_handler(Route routes[], size_t num_routes, const char *url, const char *username) {
    for (size_t i = 0; i < num_routes; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].func(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {
        {"/hello", hello}
    };

    size_t num_routes = sizeof(routes) / sizeof(Route);

    // Simulate a user navigating to "/hello" with username "John Doe"
    route_handler(routes, num_routes, "/hello", "John Doe");

    return 0;
}