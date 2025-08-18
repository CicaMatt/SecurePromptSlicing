#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char*);
} Route;

void render_template(char* template_name, char* username) {
    printf("Template: %s\n", template_name);
    printf("Hello, %s!\n", username);
}

void hello(char* username) {
    render_template("hello.html", username);
}

typedef void (*RouteHandler)(char*);

void route_register(Route routes[], int size, const char *url, RouteHandler handler) {
    for(int i = 0; i < size; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler = handler;
            break;
        }
    }
}

void route_dispatch(Route routes[], int size, const char *url, char* username) {
    for(int i = 0; i < size; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            routes[i].handler(username);
            break;
        }
    }
}

int main() {
    Route routes[] = {{"hello/<username>", hello}};
    int route_count = sizeof(routes) / sizeof(routes[0]);

    const char* user_url = "hello/JohnDoe";
    char username[100];
    sscanf(user_url, "hello/%s", username);

    route_register(routes, route_count, "hello/<username>", hello);
    route_dispatch(routes, route_count, "hello/<username>", username);

    return 0;
}