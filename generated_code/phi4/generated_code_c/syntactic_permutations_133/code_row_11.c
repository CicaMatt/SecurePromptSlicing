#include <stdio.h>
#include <stdlib.h>

// Simulating a web framework in C
typedef struct {
    char *route;
    void (*function)();
} Application;

void start_application(Application app) {
    printf("Starting application...\n");
    app.function();
}

void home() {
    printf("Hello, World!\n");
}

int main() {
    // Create the application object with route and function
    Application app = {"/home", home};

    // Run the application (simulating visiting "/home")
    start_application(app);

    return 0;
}