#include <stdio.h>
#include <stdlib.h>

typedef void (*RequestHandler)(const char* url, const char* method);

void hello_world(const char* url, const char* method) {
    printf("Hello, World!\n");
}

int handle_request(RequestHandler handler, const char* url, const char* method) {
    if (handler != NULL) {
        handler(url, method);
    } else {
        printf("404 Not Found\n");
    }
    return 0;
}

void run_application() {
    // Simulate a request to the root URL
    handle_request(hello_world, "/", "GET");
}

int main() {
    run_application();
    return 0;
}