#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *input) {
    int length = strlen(input);
    char *escaped = malloc((length * 2 + 1) * sizeof(char));
    if (!escaped) return NULL;

    for (int i = 0; i < length; ++i) {
        switch (input[i]) {
            case '&': strcat(escaped, "&amp;"); break;
            case '<': strcat(escaped, "&lt;"); break;
            case '>': strcat(escaped, "&gt;"); break;
            default: strncat(escaped, &input[i], 1); break;
        }
    }

    return escaped;
}

char* hello(const char *username) {
    char *safe_username = escape(username);
    if (!safe_username) return NULL;

    size_t message_length = strlen(safe_username) + 8; // "Hello: " + null terminator
    char *message = malloc(message_length * sizeof(char));
    if (!message) {
        free(safe_username);
        return NULL;
    }

    snprintf(message, message_length, "Hello: %s", safe_username);

    free(safe_username);
    return message;
}

typedef struct Route {
    const char *path;
    char *(*handler)(const char*);
} Route;

void handle_request(const char *url, Route routes[], int num_routes) {
    for (int i = 0; i < num_routes; ++i) {
        if (strncmp(url, routes[i].path, strlen(routes[i].path)) == 0) {
            size_t username_len = strlen(url) - strlen(routes[i].path);
            char *username = strndup(url + strlen(routes[i].path), username_len);

            if (!username) {
                printf("Error: Memory allocation failed\n");
                return;
            }

            char *response = routes[i].handler(username);
            if (response) {
                printf("%s\n", response);
                free(response);
            } else {
                printf("Error: Failed to handle request\n");
            }

            free(username);
            return;
        }
    }
    printf("404 Not Found\n");
}

int main() {
    Route routes[] = {
        {"/hello/", hello}
    };
    int num_routes = sizeof(routes) / sizeof(Route);

    char *url = "/hello/John Doe";
    handle_request(url, routes, num_routes);

    return 0;
}