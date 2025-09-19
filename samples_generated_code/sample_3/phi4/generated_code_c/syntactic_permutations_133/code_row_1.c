#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

// Minimal WSGI-like interface for C
typedef struct {
    int (*start_response)(const char *, const char **, void (*)(const char *));
} wsgi_app;

void start_response(const char *status, const char *headers[], void (*write_body)(const char *)) {
    printf("Status: %s\n", status);
    for (int i = 0; headers[i]; i++) {
        printf("%s\n", headers[i]);
    }
}

char* hello_world(void *env) {
    start_response("200 OK", (const char *[]){"Content-Type: text/plain", NULL}, write_body);
    return "Hello, World!\n";
}

void write_body(const char *body) {
    printf("%s", body);
}

wsgi_app create_wsgi_app() {
    wsgi_app app;
    app.start_response = start_response;
    // Mapping URL to the function
    void (*handle_request)(void *) = hello_world;

    return (wsgi_app){.start_response = handle_request};
}

int main(void) {
    wsgi_app app = create_wsgi_app();
    void *env = NULL;  // Typically, this would hold environment variables
    char* response = app.start_response(env);
    write_body(response);
    return 0;
}