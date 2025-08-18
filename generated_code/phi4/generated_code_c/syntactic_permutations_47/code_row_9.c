#include <stdio.h>
#include <string.h>

// Function declaration with a decorator-like behavior using macro
#define DECORATOR(url, func) \
    void handle_##func(const char* request_url) { \
        if (strcmp(request_url, url) == 0) { \
            func(); \
        } else { \
            printf("URL does not match.\n"); \
        } \
    }

// Example function to be decorated
void my_function() {
    printf("Function triggered by URL.\n");
}

int main() {
    // Decorate the function with a specific URL
    DECORATOR("/example", my_function);

    // Simulate a request to trigger the function
    handle_my_function("/example");  // Should trigger the function
    handle_my_function("/other-url"); // Should not trigger

    return 0;
}