#include <stdio.h>
#include <stdlib.h>
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

char* escape(const char *input) {
    static char output[256];
    strcpy(output, input);
    for (size_t i = 0; output[i]; i++) {
        if (output[i] == '<') {
            memmove(&output[i + 4], &output[i + 1], strlen(&output[i + 1]) + 1);
            strncpy(&output[i], "&lt;", 4);
            i += 3;
        } else if (output[i] == '>') {
            memmove(&output[i + 4], &output[i + 1], strlen(&output[i + 1]) + 1);
            strncpy(&output[i], "&gt;", 4);
            i += 3;
        }
    }
    return output;
}

void hello(char *username) {
    char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    printf("%s\n", greeting);
}

void dispatch(const char *path) {
    for (int i = 0; i < route_count; i++) {
        if (strcmp(routes[i].url, path) == 0) {
            char username[128];
            sscanf(path, "/hello/%[^/]", username);
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    add_route("/hello/%s", hello);
    dispatch("/hello/user");
    return 0;
}