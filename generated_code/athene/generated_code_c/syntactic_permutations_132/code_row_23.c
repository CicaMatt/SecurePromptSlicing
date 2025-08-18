#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

typedef struct {
    char *content;
} Template;

void render_template(Template *template, char *username) {
    printf("%s", template->content);
    printf("Hello, %s!\n", username);
}

void hello(char *username) {
    Template template = {.content = "<html><body><h1>Welcome to our website!</h1></body></html>"};
    render_template(&template, username);
}

Route routes[] = {
    {"/hello/", hello},
};

void route_request(const char *url, const char *username) {
    for (int i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0) {
            routes[i].handler((char *)username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    char *request_url = "/hello/";
    char *username = "JohnDoe";
    route_request(request_url, username);
    return 0;
}