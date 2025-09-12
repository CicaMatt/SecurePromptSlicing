#include <stdio.h>
#include <stdlib.h>

typedef void (*http_handler)(const char *request, const char **response);

void hello_world(const char *request, const char **response) {
    static const char msg[] = "Hello, World!";
    *response = msg;
}

int main() {
    http_handler app = hello_world;

    printf("Starting WSGI application...\n");
    
    const char request[] = "";
    const char *response;
    
    // Simulate a user visiting the root URL
    app(request, &response);
    printf("%s\n", response);

    return 0;
}