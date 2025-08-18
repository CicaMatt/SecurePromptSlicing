#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)(const char*);
} route_t;

typedef struct {
    route_t routes[10];
    int count;
} router_t;

router_t router = { .count = 0 };

void add_route(const char* url, const char* (*handler)(const char*)) {
    router.routes[router.count].func = handler;
    router.count++;
}

const char* escape_html(const char* input) {
    static char output[1024];
    memset(output, 0, sizeof(output));
    for (size_t i = 0; i < strlen(input); i++) {
        switch (input[i]) {
            case '<': strcat(output, "&lt;"); break;
            case '>': strcat(output, "&gt;"); break;
            case '&': strcat(output, "&amp;"); break;
            case '"': strcat(output, "&quot;"); break;
            default: strncat(output, &input[i], 1); break;
        }
    }
    return output;
}

const char* hello(const char* username) {
    static char greeting[1024];
    sprintf(greeting, "Hello %s", escape_html(username));
    return greeting;
}

void handle_request(const char* url, const char* param) {
    for (int i = 0; i < router.count; i++) {
        if (strcmp(url, "/hello/") == 0 && router.routes[i].func != NULL) {
            printf("%s\n", router.routes[i].func(param));
            return;
        }
    }
}

int main() {
    add_route("/hello/", hello);
    handle_request("/hello/", "username");
    return 0;
}