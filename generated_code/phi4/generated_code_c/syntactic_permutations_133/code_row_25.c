#include <stdio.h>
#include <stdlib.h>

// Mockup for WSGI application class and decorator functionality in C
typedef struct {
    void (*func)(void);
    const char *url;
} WebApp;

WebApp create_web_app(void (*func)(void), const char *url) {
    WebApp app = {func, url};
    return app;
}

void run_application(WebApp app, const char *requested_url) {
    if (app.url && strcmp(app.url, requested_url) == 0) {
        app.func();
    } else {
        printf("404 Not Found\n");
    }
}

// Function to be called when the user visits the specified URL
void hello_world(void) {
    printf("Hello, World!\n");
}

int main() {
    // Create application object with a decorator-like behavior
    WebApp app = create_web_app(hello_world, "/");

    // Simulate running the application with a specific URL
    run_application(app, "/");  // Change to "/" or any other string to test

    return 0;
}