#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *path;
    void (*function)(const char *);
} Route;

void escape(const char *input, char *output) {
    while (*input) {
        switch (*input) {
            case '&': strcpy(output, "&amp;"); break;
            case '<': strcpy(output, "&lt;"); break;
            case '>': strcpy(output, "&gt;"); break;
            default: *output = *input; break;
        }
        input++;
        output++;
    }
    *output = '\0';
}

void hello(const char *username) {
    char escaped_username[256];
    escape(username, escaped_username);
    
    char response[512];
    snprintf(response, sizeof(response), "Hello, %s!", escaped_username);
    printf("%s\n", response);
}

void handle_request(const char *path, const char *username) {
    Route routes[] = {
        {"/hello/", hello},
        {NULL, NULL}
    };

    for (int i = 0; routes[i].path != NULL; i++) {
        if (strncmp(path, routes[i].path, strlen(routes[i].path)) == 0) {
            routes[i].function(username);
            return;
        }
    }

    printf("404 Not Found\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <URL> <username>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    const char *username = argv[2];

    handle_request(url, username);

    return 0;
}