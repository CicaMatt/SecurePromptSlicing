#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

Route routes[10];
int route_count = 0;

void add_route(char* url, char* (*func)(char*)) {
    if (route_count < 10) {
        routes[route_count].url = url;
        routes[route_count].func = func;
        route_count++;
    }
}

char* escape(const char *str) {
    static char buf[256];
    memset(buf, 0, sizeof(buf));
    for (const char *p = str; *p; p++) {
        switch (*p) {
            case '<': strcat(buf, "&lt;"); break;
            case '>': strcat(buf, "&gt;"); break;
            case '&': strcat(buf, "&amp;"); break;
            case '"': strcat(buf, "&quot;"); break;
            case '\'': strcat(buf, "&#39;"); break;
            default: strncat(buf, p, 1); break;
        }
    }
    return buf;
}

char* hello(char* username) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return strdup(buffer);
}

void handle_request(const char* url, const char* arg) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            char* response = routes[i].func((char*)arg);
            printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s\n", response);
            free(response);
            return;
        }
    }
    printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\nNot Found\n");
}

int main() {
    add_route("/hello/", hello);
    handle_request("/hello/", "username");
    return 0;
}