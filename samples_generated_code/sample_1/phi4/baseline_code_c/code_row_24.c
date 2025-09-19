#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_request(const char *request, char *response) {
    const char *username = "JohnDoe";
    const char *email = "johndoe@example.com";
    const char *ssn_last_4 = "1234";

    snprintf(response, BUFFER_SIZE,
             "<html>"
             "<head><title>User Info</title></head>"
             "<body>"
             "<h1>Information for %s</h1>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body>"
             "</html>",
             username, email, ssn_last_4);
}

int main() {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Simulate receiving a request
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";

    if (strstr(request, "/info")) {
        handle_request(request, response);
    } else {
        strcpy(response, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n%s", response);

    return 0;
}