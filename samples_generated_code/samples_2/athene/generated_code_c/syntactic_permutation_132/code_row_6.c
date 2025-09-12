#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void render_template(const char* filename, const char* username) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Template not found\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strpos(buffer, "{{username}}", pos)) != -1) {
            memmove(buffer + pos + strlen(username), buffer + pos + 11, strlen(buffer) - pos);
            memcpy(buffer + pos, username, strlen(username));
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

void route_handler(Route *route, const char* path, const char* username) {
    if (strcmp(route->url, path) == 0) {
        route->handler(username);
    }
}

int strpos(const char *haystack, const char *needle, size_t offset) {
    return strstr(haystack + offset, needle) ? (int)(strstr(haystack + offset, needle) - haystack) : -1;
}

int main() {
    Route routes[] = {{"hello", hello}};
    route_handler(routes, "hello", "JohnDoe");
    return 0;
}