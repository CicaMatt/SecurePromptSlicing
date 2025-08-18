#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

void send_http_response(const char *status, const char *content_type, const char *body) {
    printf("HTTP/1.1 %s\r\n", status);
    printf("Content-Type: %s\r\n", content_type);
    printf("Connection: close\r\n");
    printf("\r\n%s", body);
}

void info() {
    const char *username = SESSION_USERNAME;
    const char *email = SESSION_EMAIL;
    const char *ssn = SESSION_SSN;

    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>Info</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>", username, email, ssn + strlen(ssn) - 4);

    send_http_response("200 OK", "text/html", response);
}

void handle_request(const char *request_line) {
    if (strncmp(request_line, "GET /info HTTP/", 15) == 0) {
        info();
    } else {
        const char *not_found = "<html><body><h1>404 Not Found</h1></body></html>";
        send_http_response("404 Not Found", "text/html", not_found);
    }
}

int main() {
    char request_line[256];

    // Simulate a client request
    strcpy(request_line, "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    handle_request(request_line);

    return 0;
}