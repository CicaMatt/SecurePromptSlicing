#include <stdio.h>

// Simulated Web Application Class for WSGI-like behavior in C
typedef struct {
    const char* (*call)(const char*);
} WebApplication;

// Decorator function to associate URL with a handler
void route(WebApplication *app, const char* url) {
    static void (*handler_func)(const char*) = NULL;
    // Simple if-else to bind the right function based on the URL
    if (strcmp(url, "/") == 0) {
        handler_func = handle_root;
    }
}

// Handler function for the root URL
const char* handle_root(const char* request) {
    return "Hello, World!";
}

int main() {
    // Create an instance of WebApplication
    WebApplication my_app = { .call = NULL };

    // Decorate the root route with its handler
    route(&my_app, "/");

    // Call the handler function and print the response
    const char* response = my_app.call("/");
    printf("%s\n", response);

    return 0;
}