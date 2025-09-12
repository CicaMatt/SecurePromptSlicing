#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

void render_template(const char* filename, const char* username) {
    printf("Template: %s\n", filename);
    printf("Hello, %s!\n", username);
}

void hello(char* username) {
    render_template("hello.html", username);
}

Route routes[] = {{"^/hello/(.*)$", hello}};

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    const char* url = argv[1];
    for (size_t i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        Route route = routes[i];
        char pattern[100], username[100];
        snprintf(pattern, sizeof(pattern), "^[^/]+/%s", route.url);
        if (sscanf(url, pattern, username) == 1) {
            route.handler(username);
            return 0;
        }
    }
    return 1;
}