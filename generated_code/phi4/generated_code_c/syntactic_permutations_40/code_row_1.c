#include <stdio.h>
#include <string.h>

// Simulating a web server environment using C standard libraries

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

Session current_session = {"johndoe", "john.doe@example.com", "1234"};

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html>\n<head><title>Info</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", current_session.username);
    printf("<p>Email: %s</p>\n", current_session.email);
    printf("<p>Last 4 digits of SSN: %s</p>\n", current_session.ssn_last_4);
    printf("</body></html>\n");
}

void handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 21) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>\n");
    }
}

int main() {
    char request[1024];

    // Simulating a client making a GET request to /info
    strcpy(request, "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    handle_request(request);

    return 0;
}