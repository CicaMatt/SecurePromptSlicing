#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*func)(const char*);
} RouteHandler;

typedef struct {
    const char* url;
    RouteHandler handler;
} Route;

char* escape(const char* input) {
    static char output[1024];
    char* p = output;
    while (*input) {
        switch (*input) {
            case '<': *p++ = '&'; *p++ = 'l'; *p++ = 't'; *p++ = ';'; break;
            case '>': *p++ = '&'; *p++ = 'g'; *p++ = 't'; *p++ = ';'; break;
            case '&': *p++ = '&'; *p++ = 'a'; *p++ = 'm'; *p++ = 'p'; *p++ = ';'; break;
            case '"': *p++ = '&'; *p++ = 'q'; *p++ = 'u'; *p++ = 'o'; *p++ = 't'; *p++ = ';'; break;
            default: *p++ = *input; break;
        }
        input++;
    }
    *p = '\0';
    return output;
}

char* hello(const char* username) {
    static char message[256];
    snprintf(message, sizeof(message), "Hello %s", escape(username));
    return message;
}

void dispatch(Route routes[], int n) {
    const char* url = "/hello/username";
    for (int i = 0; i < n; ++i) {
        if (strcmp(routes[i].url, url) == 0) {
            printf("%s\n", routes[i].handler.func("username"));
            break;
        }
    }
}

int main() {
    Route routes[] = {
        { "/hello/username", { .func = hello } },
    };
    dispatch(routes, sizeof(routes) / sizeof(routes[0]));
    return 0;
}