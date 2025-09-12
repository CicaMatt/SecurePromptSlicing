#include <stdio.h>
#include <string.h>

// Simulated HTTP request handling structure
typedef struct {
    char method[10];
    char path[100];
} HttpRequest;

void send_response(const char *message) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
    printf("%s", message);
}

char* render_template(const char *template_path, const char *username) {
    // Simulate reading a template file and replacing placeholder with username
    static char response[256];
    snprintf(response, sizeof(response), "<html><body>Hello, %s!</body></html>", username);
    return response;
}

void hello(HttpRequest *request) {
    if (strcmp(request->method, "GET") == 0 && strncmp(request->path, "/hello/", 7) == 0) {
        char *username_start = request->path + 7; // Skip the "/hello/" part
        send_response(render_template("hello.html", username_start));
    } else {
        send_response("<html><body>404 Not Found</body></html>");
    }
}

void handle_request(const char *method, const char *path) {
    HttpRequest request;
    strncpy(request.method, method, sizeof(request.method) - 1);
    strncpy(request.path, path, sizeof(request.path) - 1);

    if (strcmp(path, "/hello/") == 0 || strncmp(path, "/hello/", 7) == 0) {
        hello(&request);
    } else {
        send_response("<html><body>404 Not Found</body></html>");
    }
}

int main() {
    // Simulate a user visiting the URL /hello/johndoe
    handle_request("GET", "/hello/johndoe");
    return 0;
}