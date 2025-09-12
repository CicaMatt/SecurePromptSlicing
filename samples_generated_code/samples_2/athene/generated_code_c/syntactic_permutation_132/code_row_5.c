#include <stdio.h>
#include <string.h>

#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *url;
    void (*func)(char *);
} Route;

void render_template(const char *file, const char *username) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Template not found\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);
    printf("<h1>Hello, %s!</h1>", username);
}

void hello(char *username) {
    render_template(TEMPLATE_FILE, username);
}

void route_handler(Route routes[], int count, char *url, char *username) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].func(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {{"hello", hello}};
    int route_count = sizeof(routes) / sizeof(routes[0]);

    char *url = "/hello/user123";
    char *username = "user123";

    // Simulate the URL being hit
    route_handler(routes, route_count, url + 1, username);

    return 0;
}