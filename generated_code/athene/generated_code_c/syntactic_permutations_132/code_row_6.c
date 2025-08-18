#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} Route;

void render_template(const char *template, const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (!file) {
        perror("Failed to open template file");
        exit(1);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; i++) {
            if (buffer[i] == '$' && i + 1 < len && buffer[i + 1] == 'u') {
                printf("%s", username);
                i++;
            } else {
                putchar(buffer[i]);
            }
        }
    }
    fclose(file);
}

void hello(const char *username) {
    render_template("hello.html", username);
}

void route_handler(Route route, const char *path) {
    if (strcmp(route.url, path) == 0) {
        route.handler(path + strlen("/hello/"));
    }
}

int main() {
    Route routes[] = {
        {"/hello/", hello},
        // Add more routes here
    };
    const char *user_path = "/hello/user123";
    for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); i++) {
        route_handler(routes[i], user_path);
    }
    return 0;
}