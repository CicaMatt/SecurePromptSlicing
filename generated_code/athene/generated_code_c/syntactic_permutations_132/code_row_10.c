#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *username);
} Route;

void render_template(const char *template, const char *username) {
    printf("Template: %s\n", template);
    printf("Username: %s\n", username);
}

void hello(char *username) {
    const char *template = "<html><body>Hello, {{username}}!</body></html>";
    char rendered_template[1024];
    snprintf(rendered_template, sizeof(rendered_template), template, username);
    render_template(rendered_template, username);
}

Route routes[] = {
    {"/hello/", hello},
};

void handle_request(const char *url, const char *username) {
    for (int i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0) {
            routes[i].handler(strdup(username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    const char *url = "/hello/JohnDoe";
    const char *username = url + strlen("/hello/");
    handle_request(url, username);
    return 0;
}