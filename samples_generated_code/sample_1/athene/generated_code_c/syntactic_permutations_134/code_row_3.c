#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*handler)(char*);
} Route;

void add_route(Route routes[], int *route_count, char* url, char* (*handler)(char*)) {
    routes[*route_count].url = url;
    routes[*route_count].handler = handler;
    (*route_count)++;
}

char* escape(const char *s) {
    static char escaped[1024];
    strcpy(escaped, "");
    for (const char *p = s; *p; p++) {
        switch (*p) {
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            case '&': strcat(escaped, "&amp;"); break;
            case '"': strcat(escaped, "&quot;"); break;
            case '\'': strcat(escaped, "&#39;"); break;
            default: strncat(escaped, p, 1); break;
        }
    }
    return escaped;
}

char* hello_user(char *username) {
    static char response[1024];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(Route routes[], int route_count, const char* url, const char* username) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            printf("%s\n", routes[i].handler((char*)username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[10];
    int route_count = 0;

    add_route(routes, &route_count, "/user/", hello_user);

    const char* url = "/user/";
    const char* username = "John Doe";
    handle_request(routes, route_count, url, username);

    return 0;
}