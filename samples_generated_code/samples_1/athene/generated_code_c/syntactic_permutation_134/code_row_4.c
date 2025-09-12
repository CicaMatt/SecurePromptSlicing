#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

#define MAX_ROUTES 10
Route routes[MAX_ROUTES];
int route_count = 0;

void add_route(const char* url, char* (*func)(char*)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].url = strdup(url);
        routes[route_count].func = func;
        route_count++;
    }
}

char* escape_html(const char* str) {
    static char buffer[1024];
    const char *html_escapes[] = {"&", "&amp;", "<", "&lt;", ">", "&gt;", "\"", "&quot;"};
    char* p = buffer;
    while (*str) {
        int i;
        for (i = 0; i < 4; i += 2) {
            if (*str == html_escapes[i][0]) {
                strcpy(p, html_escapes[i + 1]);
                p += strlen(html_escapes[i + 1]);
                break;
            }
        }
        if (i == 8) {
            *p++ = *str;
        }
        str++;
    }
    *p = '\0';
    return buffer;
}

char* hello(char* username) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello, %s!", escape_html(username));
    return strdup(buffer);
}

void handle_request(const char* url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            printf("%s\n", routes[i].func(url + strlen("/hello/")));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/", hello);
    handle_request("/hello/user123");
    return 0;
}