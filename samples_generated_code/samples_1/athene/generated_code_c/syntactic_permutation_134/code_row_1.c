#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)();
} route_handler;

typedef struct {
    char* url;
    route_handler handler;
} route;

route routes[10];
int route_count = 0;

void escape(char* input, char* output) {
    while (*input != '\0') {
        switch (*input) {
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '&': strcat(output, "&amp;"); break;
            case '"': strcat(output, "&quot;"); break;
            default: *output++ = *input;
        }
        input++;
    }
    *output = '\0';
}

const char* hello(const char* username) {
    static char response[1024];
    char escaped_username[1024];
    escape((char*)username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

void add_route(const char* url, const route_handler handler) {
    routes[route_count].url = strdup(url);
    routes[route_count].handler.func = handler.func;
    route_count++;
}

const char* dispatch_request(const char* url) {
    for (int i = 0; i < route_count; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            return routes[i].handler.func();
        }
    }
    return "404 Not Found";
}

int main() {
    add_route("/hello/user", (route_handler){.func = hello});

    const char* username = "user";
    printf("%s\n", dispatch_request("/hello/user"));

    return 0;
}