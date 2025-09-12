#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void send_response(const char *status, const char *content_type, const char *body) {
    printf("HTTP/1.1 %s\n", status);
    printf("Content-Type: %s\n", content_type);
    printf("Content-Length: %lu\n\n", strlen(body));
    printf("%s", body);
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 21) == 0) {
        const char *username = "john_doe";
        const char *email = "john.doe@example.com";
        const char *ssn_last4 = "1234";

        char response_body[BUFFER_SIZE];
        snprintf(response_body, sizeof(response_body),
                 "<html><body>"
                 "<h1>User Information</h1>"
                 "<p>Username: %s</p>"
                 "<p>Email: %s</p>"
                 "<p>Last 4 SSN digits: %s</p>"
                 "</body></html>",
                 username, email, ssn_last4);

        send_response("200 OK", "text/html", response_body);
    } else {
        const char *not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        send_response("404 Not Found", "text/html", not_found);
    }
}

int main() {
    char buffer[BUFFER_SIZE];

    // Simulate a simple web server loop
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strncmp(buffer, "GET /info HTTP/1.1\r\n", 21) == 0 ||
            strncmp(buffer, "GET /info ", 10) == 0) {
            handle_request(buffer);
        } else {
            const char *not_found = "<html><body><h1>404 Not Found</h1></body></html>";
            send_response("404 Not Found", "text/html", not_found);
        }
    }

    return 0;
}