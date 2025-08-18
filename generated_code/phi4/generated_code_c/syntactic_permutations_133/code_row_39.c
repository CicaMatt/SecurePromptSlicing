#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *url;
    void (*handler)(const char *);
} WebApp;

void hello_handler(const char *request) {
    printf("Hello, World!\n");
}

int main() {
    WebApp app = {"/", hello_handler};

    // Simulating a request to the root URL
    if (app.url && strcmp(app.url, "/") == 0) {
        app.handler(NULL);
    }

    return 0;
}