#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock implementation for demonstration purposes

typedef struct {
    char *url;
    void (*func)(const char*);
} Route;

Route routes[10];
int route_count = 0;

void app(const char* url) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].func(url + strlen("/hello/"));
            return;
        }
    }
    printf("404 Not Found\n");
}

void route(const char* url, void (*func)(const char*)) {
    routes[route_count].url = strdup(url);
    routes[route_count++].func = func;
}

void render_template(const char* template_name, const char* username) {
    FILE *template_file = fopen(template_name, "r");
    if (template_file == NULL) {
        printf("Template not found\n");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), template_file)) {
        if (strstr(buffer, "{{ username }}")) {
            printf("%.*s%s%s\n", 
                   (int)(strstr(buffer, "{{ username }}") - buffer),
                   buffer,
                   username,
                   strstr(buffer, "}}") + 2);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(template_file);
}

void hello(const char* username) {
    render_template("hello.html", username);
}

int main() {
    route("/hello/<username>", hello);

    // Simulate a request
    app("/hello/Alice");

    return 0;
}