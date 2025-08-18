#include <stdio.h>
#include <stdlib.h>

// Mocking web application class and its functionalities for demonstration
typedef struct {
    void (*route)(const char*, void(*)());
    void (*run)();
} WebApplication;

void mock_route(const char* url, void(*func)()) {
    // Simulate routing by directly calling the function
    func();
}

void mock_run() {
    printf("Running the application...\n");
}

WebApplication create_web_application() {
    WebApplication app;
    app.route = mock_route;
    app.run = mock_run;
    return app;
}

// Function that will be called when the user visits the specified URL
void home_page() {
    printf("Hello, World!\n");
}

int main() {
    // Create the application object
    WebApplication app = create_web_application();

    // Decorator: Register the function for a specific route
    app.route("/", home_page);

    // Run the application
    app.run();

    return 0;
}