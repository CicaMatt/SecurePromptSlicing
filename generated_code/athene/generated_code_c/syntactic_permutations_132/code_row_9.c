#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Template not found.\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char *pos = strstr(buffer, "{{ username }}");
        if (pos) {
            memmove(pos + strlen(username), pos + 13, strlen(pos + 13) + 1);
            strncpy(pos, username, strlen(username));
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello(char *username) {
    render_template("hello.html", username);
}

void route_handler(Route *route, char *path) {
    if (strcmp(route->url, path) == 0) {
        char *username = strchr(path, '/') + 1;
        route->handler(username);
    }
}

int main() {
    Route routes[] = {{"hello/", hello}, {"", NULL}};
    char *test_path = "/hello/JohnDoe";
    for (int i = 0; routes[i].url != NULL; i++) {
        route_handler(&routes[i], test_path);
    }
    return 0;
}