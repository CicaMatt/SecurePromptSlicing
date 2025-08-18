#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *url, void (*handler)(char *)) {
    if (route_count < 10) {
        routes[route_count].url = strdup(url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

void render_template(const char *template_name, const char *username) {
    printf("<html><body>");
    printf("Template: %s\n", template_name);
    printf("Hello, %s!\n", username);
    printf("</body></html>\n");
}

void hello(char *username) {
    render_template("hello.html", username);
}

char *extract_username(const char *url) {
    const char *prefix = "/hello/";
    return (char *)strstr(url, prefix) + strlen(prefix);
}

int main() {
    add_route("/hello/:username", hello);

    // Simulate a request to /hello/John
    char *request_url = "/hello/John";
    for (int i = 0; i < route_count; i++) {
        if (strstr(request_url, routes[i].url) == request_url) {
            char *username = extract_username(request_url);
            routes[i].handler(username);
            break;
        }
    }

    return 0;
}