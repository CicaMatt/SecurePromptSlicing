#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *(*func)(void *self, char *path);
} wsgi_app;

void *hello_world(void *self, char *path) {
    (void) self;
    if (strcmp(path, "/hello") == 0) {
        return "Hello, World!\n";
    }
    return "Not Found\n";
}

int main() {
    wsgi_app app = { hello_world };
    char path[256];
    printf("Enter the URL path: ");
    fgets(path, sizeof(path), stdin);
    // Remove newline character
    size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') {
        path[--len] = '\0';
    }
    
    char *response = app.func(NULL, path);
    printf("%s", response);

    return 0;
}