#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple web server framework in C for demonstration

typedef struct {
    char *path;
    void (*handler)(char*);
} Route;

void render_template(char* username) {
    printf("Hello, %s! Welcome to our website.\n", username);
}

void hello(char* username) {
    render_template(username);
}

Route routes[] = {
    {"/hello/", hello},
};

void handle_request(char* request_path) {
    char* path = strdup(request_path);
    char* token = strtok(path, "/");
    token = strtok(NULL, "/"); // Skip the first empty or 'hello' part

    if (token != NULL) {
        for (int i = 0; i < sizeof(routes)/sizeof(Route); i++) {
            if (strcmp(routes[i].path, "/hello/") == 0) {
                routes[i].handler(token);
                break;
            }
        }
    }

    free(path);
}

int main() {
    handle_request("/hello/Alice");
    return 0;
}