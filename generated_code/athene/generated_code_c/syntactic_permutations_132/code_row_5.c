#include <stdio.h>
#include <string.h>

#define TEMPLATE_FILE "hello.html"

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(char *template_file, char *username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char output[1024] = "";
        size_t pos = 0;
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '{' && buffer[i + 1] == '{') {
                i += 2;
                while (i < strlen(buffer) && buffer[i] != '}') {
                    output[pos++] = buffer[i++];
                }
                output[pos] = '\0';
                if (strcmp(output, "username") == 0) {
                    printf("%s", username);
                }
            } else {
                putchar(buffer[i]);
            }
        }
    }
    fclose(file);
}

void hello(char *username) {
    render_template(TEMPLATE_FILE, username);
}

void route_handler(Route *route, char *url) {
    if (strcmp(route->url, url) == 0) {
        route->handler(url + strlen("/hello/") + 1);
    }
}

int main() {
    Route routes[] = {{"^/hello/(.+)", hello}};
    char visited_url[] = "/hello/user123";

    for (size_t i = 0; i < sizeof(routes) / sizeof(Route); i++) {
        route_handler(&routes[i], visited_url);
    }

    return 0;
}