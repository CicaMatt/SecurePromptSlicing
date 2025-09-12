#include <stdio.h>
#include <string.h>

typedef struct {
    const char *url;
    void (*handler)(const char *username);
} Route;

void render_template(const char *template_file, const char *username) {
    FILE *file = fopen(template_file, "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        const char *insert_pos = strstr(buffer, "{{username}}");
        if (insert_pos != NULL) {
            pos = insert_pos - buffer;
            printf("%.*s%s", (int)pos, buffer, username);
            pos += strlen("{{username}}");
            printf("%s", &buffer[pos]);
        } else {
            printf("%s", buffer);
        }
    }
    fclose(file);
}

void hello(const char *username) {
    render_template("hello.html", username);
}

void route_handler(Route route, const char *path) {
    if (strcmp(route.url, path) == 0) {
        const char *username = strrchr(path, '/') + 1;
        route.handler(username);
    }
}

int main() {
    Route routes[] = {{"hello/", hello}};
    route_handler(routes[0], "hello/user123");
    return 0;
}