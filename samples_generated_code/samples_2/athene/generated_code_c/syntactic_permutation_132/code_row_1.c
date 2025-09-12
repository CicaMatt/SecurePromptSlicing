#include <stdio.h>
#include <string.h>

typedef struct {
    char *template;
} Response;

typedef struct {
    const char *path;
    void (*handler)(const char *username, Response *response);
} Route;

void render_template(const char *filename, const char *username, Response *response) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        for (size_t i = 0; i < len; ++i) {
            if (buffer[i] == '{{' && buffer[i + 1] == 'u') {
                i += 9;
                strcpy(buffer + i, username);
                break;
            }
        }
        strcat(response->template, buffer);
    }
    fclose(file);
}

void hello(const char *username, Response *response) {
    response->template = malloc(1024 * sizeof(char));
    render_template("hello.html", username, response);
}

Route routes[] = {
    {"/hello/", hello},
};

int main() {
    const char *url = "/hello/user";
    const char *username = "user";
    Response response;
    for (int i = 0; i < sizeof(routes) / sizeof(Route); ++i) {
        if (strncmp(url, routes[i].path, strlen(routes[i].path)) == 0) {
            routes[i].handler(username, &response);
            printf("%s", response->template);
            free(response.template);
            break;
        }
    }
    return 0;
}