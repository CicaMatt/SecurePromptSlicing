#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} web_application;

web_application app;  // Create the application object

#define route(url, func) void handle_##func()  // Decorator simulation
route("/", index) {  // URL and associated function
    printf("Hello, World!");  // Message to return to user
}

int main() {
    // Simulate running the application
    handle_index();
    return 0;
}