#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

void route(Route routes[], int size, const char* path, char* username) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(routes[i].url, path) == 0) {
            printf("%s", routes[i].func(username));
            return;
        }
    }
}

char* escape(char* input) {
    static char output[1024];
    strcpy(output, input);
    // Simple escaping for demonstration purposes
    char *p = output;
    while (*p) {
        if (*p == '<') {
            memmove(p + 4, p + 1, strlen(p));
            strncpy(p, "&lt;", 4);
            p += 3;
        } else if (*p == '>') {
            memmove(p + 4, p + 1, strlen(p));
            strncpy(p, "&gt;", 4);
            p += 3;
        }
        ++p;
    }
    return output;
}

char* hello(char* username) {
    static char greeting[1024];
    sprintf(greeting, "Hello %s", escape(username));
    return greeting;
}

int main() {
    Route routes[] = {{"hello", hello}};
    int route_count = sizeof(routes) / sizeof(Route);

    // Simulate navigating to the URL
    char* path = "/hello/user123";
    char username[1024];
    sscanf(path, "/hello/%s", username);
    route(routes, route_count, "hello", username);

    return 0;
}