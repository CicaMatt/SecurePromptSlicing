#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(char *template, char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char *output = strdup(buffer);
        size_t pos = 0;
        if ((pos = strstr(output, "{{username}}")) != NULL) {
            memmove(pos + strlen(username), pos + 12, strlen(pos + 12) + 1);
            memcpy(pos, username, strlen(username));
        }
        printf("%s", output);
        free(output);
    }
    fclose(file);
}

void hello(char *username) {
    render_template("hello.html", username);
}

void route_handler(Route *route, char *path) {
    if (strcmp(route->url, path) == 0) {
        route->handler(path + strlen("/hello/"));
    }
}

int main() {
    Route routes[] = {{"^/hello/(.*)$", hello}, {NULL, NULL}};
    char *request_path = "/hello/user123";
    
    for (int i = 0; routes[i].url != NULL; i++) {
        route_handler(&routes[i], request_path);
    }

    return 0;
}