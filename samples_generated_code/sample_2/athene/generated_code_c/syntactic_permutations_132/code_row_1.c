#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* template_file, const char* username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("<p>Welcome %s!</p>", username);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

void route_handler(Route routes[], int num_routes, const char* url) {
    for (int i = 0; i < num_routes; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            char username[100];
            sscanf(url, "/hello/%s", username);
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {{"^/hello/(.*)$", hello}};
    int num_routes = sizeof(routes) / sizeof(Route);

    const char* url = "/hello/user123";
    route_handler(routes, num_routes, url);

    return 0;
}