#include <stdio.h>
#include <stdlib.h>

// Dummy Web Application Class for demonstration purposes
typedef struct {
    void (*handle)(const char *url);
} WSGIApplication;

WSGIApplication create_application() {
    WSGIApplication app;
    app.handle = NULL; // Initialize with no handler
    return app;
}

void register_handler(WSGIApplication *app, const char *url, void(*handler)(const char *)) {
    if (strcmp(url, "/") == 0) { // Check URL for the decorator equivalent
        app->handle = handler;
    }
}

// Function to be called by WSGI application when URL matches
void hello_world(const char *url) {
    printf("Hello, World!\n");
}

int main() {
    WSGIApplication app = create_application();
    
    // Register the function for a specific URL (Decorator equivalent)
    register_handler(&app, "/", hello_world);

    // Simulate a request to "/"
    if(app.handle != NULL) {
        app.handle("/");  // Call the associated handler
    }

    return 0;
}