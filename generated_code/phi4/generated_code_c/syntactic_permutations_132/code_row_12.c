#include <stdio.h>
#include <string.h>

// Simulating a basic HTTP server request handler in C
void handle_request(const char *path, const char *username) {
    if (strcmp(path, "/hello/") == 0 && username != NULL) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n");
        printf("<html>\n<head><title>Hello</title></head>\n<body>");
        printf("<h1>Hello, %s!</h1>", username);
        printf("</body>\n</html>");
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html>\n<head><title>Not Found</title></head>\n<body>");
        printf("<h1>404 Page Not Found</h1>");
        printf("</body>\n</html>");
    }
}

int main() {
    // Example usage
    handle_request("/hello/john", "john");
    
    return 0;
}