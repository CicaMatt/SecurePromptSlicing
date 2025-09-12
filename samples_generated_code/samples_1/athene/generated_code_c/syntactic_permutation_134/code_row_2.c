#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *url;
    void (*func)(char *);
} Route;

Route routes[10];
int route_count = 0;

void escape(char *str) {
    for (char *p = str; *p; p++) {
        if (*p == '<') {
            printf("&lt;");
        } else if (*p == '>') {
            printf("&gt;");
        } else if (*p == '&') {
            printf("&amp;");
        } else if (*p == '"') {
            printf("&quot;");
        } else if (*p == '\'') {
            printf("&#39;");
        } else {
            putchar(*p);
        }
    }
}

void route(char *url, void (*func)(char *)) {
    routes[route_count].url = url;
    routes[route_count].func = func;
    route_count++;
}

void hello(char *username) {
    printf("Hello ");
    escape(username);
    printf("\n");
}

int main() {
    route("/hello/username", hello);

    // Simulate a request to /hello/username
    char *username = "user<name>";
    if (route_count > 0 && routes[0].url != NULL) {
        routes[0].func(username);
    }

    return 0;
}