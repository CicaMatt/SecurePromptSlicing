#include <stdio.h>
#include <stdlib.h>

// Mock WSGI web application class and methods for illustration purposes.
typedef struct {
    void (*run)(void);
} WSGIApp;

void call_function(void) {
    printf("Hello, User!\n");
}

WSGIApp* create_application() {
    WSGIApp *app = (WSGIApp*)malloc(sizeof(WSGIApp));
    app->run = call_function;
    return app;
}

int main() {
    // Line 2: Create the application object
    WSGIApp* app = create_application();

    // Line 6: Runs the application
    app->run();
    
    free(app);
    return 0;
}