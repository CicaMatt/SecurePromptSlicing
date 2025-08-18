#include <stdio.h>

typedef struct {
    // Web application properties and methods would be defined here
} web_application;

void decorator(web_application *app, char *url, void (*func)(char *)) {
    // Decorator function to map URLs to functions
}

void hello_world(char *message) {
    printf("%s", message);
}

int main() {
    web_application app; // Create the application object
    decorator(&app, "/", hello_world); // Map URL '/' to hello_world function

    // Simulate running the application (in a real WSGI app, this would start a server)
    char *user_message = "Hello, World!";
    hello_world(user_message);

    return 0;
}