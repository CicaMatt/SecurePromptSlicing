#include <stdio.h>
#include <string.h>

// Dummy WSGI application class for demonstration purposes.
typedef struct {
    void (*run)(void);
} WebApp;

const char* home_page(const char *request_path) {
    if (strcmp(request_path, "/") == 0 || strcmp(request_path, "/home") == 0) {
        return "Welcome to the Home Page!";
    }
    return "404 Not Found";
}

void handle_request(void (*route_handler)(char *)) {
    const char* response = route_handler("/");
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s", response);
}

int main() {
    WebApp app;
    app.run = handle_request;

    // Simulate a web server handling requests
    app.run(home_page);

    return 0;
}