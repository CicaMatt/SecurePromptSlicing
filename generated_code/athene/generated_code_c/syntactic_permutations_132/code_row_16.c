#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *url;
    void (*handler)(const char *username);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *url, void (*handler)(const char *username)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].handler = handler;
        route_count++;
    }
}

void render_template(const char *template, const char *username) {
    printf(template, username);
}

void hello(const char *username) {
    render_template("Hello, %s!\n", username);
}

void dispatch_request(const char *url_path) {
    for (int i = 0; i < route_count; i++) {
        if (strstr(url_path, routes[i].url) == url_path) {
            const char *username = url_path + strlen(routes[i].url);
            if (*username == '/') username++;
            routes[i].handler(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/", hello);

    // Simulating a request
    dispatch_request("/hello/JohnDoe");

    return 0;
}