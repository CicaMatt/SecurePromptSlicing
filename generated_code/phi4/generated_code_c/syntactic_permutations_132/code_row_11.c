#include <stdio.h>
#include <string.h>

// Mock function to simulate rendering a template with a username
void render_hello_template(const char *username) {
    printf("Hello, %s!\n", username);
}

// Decorator to bind a function to a URL pattern
#define BIND_TO_URL(pattern, func) \
    void handle_request_##func(char *path) { \
        if (strncmp(path, pattern, strlen(pattern)) == 0) { \
            char *username_start = path + strlen(pattern); \
            char username[256]; \
            sscanf(username_start, "%255[^/]", username); \
            func(username); \
        } else { \
            printf("404 Not Found\n"); \
        } \
    }

// Bind the render_hello_template function to /hello/<username>
BIND_TO_URL("/hello/", render_hello_template)

int main() {
    // Simulate a user visiting the URL /hello/john
    char url[] = "/hello/john";
    handle_request_render_hello_template(url);

    return 0;
}