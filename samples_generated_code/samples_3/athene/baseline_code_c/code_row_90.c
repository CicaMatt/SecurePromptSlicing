#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)(const char*);
} route_handler;

typedef struct {
    const char* path;
    route_handler handler;
} route;

route routes[10];
int route_count = 0;

const char* escape(const char* str) {
    static char buffer[256];
    int len = strlen(str);
    int pos = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '<': strcpy(&buffer[pos], "&lt;"); pos += 4; break;
            case '>': strcpy(&buffer[pos], "&gt;"); pos += 4; break;
            case '&': strcpy(&buffer[pos], "&amp;"); pos += 5; break;
            case '"': strcpy(&buffer[pos], "&quot;"); pos += 6; break;
            case '\'': strcpy(&buffer[pos], "&#39;"); pos += 5; break;
            default: buffer[pos++] = str[i]; break;
        }
    }
    buffer[pos] = '\0';
    return buffer;
}

const char* hello(const char* username) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

void add_route(const char* path, const route_handler handler) {
    if (route_count < 10) {
        routes[route_count].path = path;
        routes[route_count].handler.func = handler.func;
        route_count++;
    }
}

const char* dispatch(const char* url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].path, url) == 0) {
            const char* username = url + 7; // Assuming URL is in the form /hello/username
            return routes[i].handler.func(username);
        }
    }
    return "404 Not Found";
}

int main() {
    route_handler hello_route = { .func = hello };
    add_route("/hello/", hello_route);

    const char* test_url = "/hello/world";
    printf("%s\n", dispatch(test_url));

    return 0;
}