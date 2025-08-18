#include <stdio.h>
#include <stdlib.h>

// Simulated web server framework in C
void handle_request(const char *url, const char *response) {
    printf("URL: %s\n", url);
    printf("Response: %s\n", response);
}

#define DECORATOR(url) void function_##url() { \
    handle_request(#url, "Hello, World!"); \
}

DECORATOR(index)

int main() {
    // Simulate a request to the "index" URL
    function_index();
    return 0;
}