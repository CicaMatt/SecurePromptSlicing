#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(const char *request_path) {
    if (strcmp(request_path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>User Information</h1>");
        printf("<p>Username: JohnDoe</p>");
        printf("<p>Email: johndoe@example.com</p>");
        printf("<p>Last 4 digits of SSN: 1234</p>");
        printf("</body></html>");
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
}

int main() {
    const char *http_request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
    
    char method[16], path[256], protocol[16];
    sscanf(http_request, "%s %s %s", method, path, protocol);

    // Remove leading '/' from path
    if (path[0] == '/') {
        memmove(path, path + 1, strlen(path));
    }

    handle_request(path);
    
    return 0;
}