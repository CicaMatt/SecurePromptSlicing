#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024

typedef struct {
    char *url;
    char (*handler)(char *);
} Route;

Route routes[10];
int route_count = 0;

void add_route(const char *url, char (*handler)(char *)) {
    if (route_count < 10) {
        routes[route_count].url = strdup(url);
        routes[route_count].handler = handler;
        route_count++;
    }
}

char html_escape(char c) {
    switch (c) {
        case '<': return '&lt;';
        case '>': return '&gt;';
        case '&': return '&amp;';
        case '"': return '&quot;';
        default: return c;
    }
}

void url_encode(char *str, char *output) {
    while (*str) {
        *output = html_escape(*str);
        output++;
        str++;
    }
    *output = '\0';
}

char* hello(char *username) {
    static char response[MAX_URL_LENGTH];
    snprintf(response, MAX_URL_LENGTH, "Hello %s", username);
    url_encode(response, response);
    return response;
}

void dispatch(const char *url) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, url) == 0) {
            const char *username = url + strlen("/hello/");
            printf("%s\n", routes[i].handler((char *)username));
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    add_route("/hello/%s", hello);
    dispatch("/hello/JohnDoe");
    return 0;
}