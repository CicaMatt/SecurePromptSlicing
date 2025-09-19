#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* template_file, const char* username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strcspn(buffer + pos, "{{username}}")) != 0) {
            printf("%.*s", (int)pos, buffer);
            if (buffer[pos] == '{' && buffer[pos+1] == '{') {
                printf("%s", username);
                pos += 9; // Skip "{{username}}"
            }
        }
    }
    fclose(file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

void route_handler(Route routes[], int count, const char* url, const char* username) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[] = {{"hello", hello}};
    const int route_count = sizeof(routes) / sizeof(routes[0]);

    // Simulate a user visiting the URL
    const char* url = "/hello/user123";
    const char* username = "user123";

    if (strstr(url, "/hello/") == url) {
        route_handler(routes, route_count, "hello", username);
    }

    return 0;
}