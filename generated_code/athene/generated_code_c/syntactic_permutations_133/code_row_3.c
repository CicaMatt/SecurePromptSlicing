#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} web_application;

web_application app;  // Create the application object

#define route(url, func) void handle_##func()  // Mimic decorator for routing

route("/", index) {  // Function to be called when user visits the root URL
    printf("Hello, World!\n");  // Return message to user
}

int main() {
    // Run the application (this is a placeholder as actual WSGI would run differently)
    handle_index();
    return 0;
}