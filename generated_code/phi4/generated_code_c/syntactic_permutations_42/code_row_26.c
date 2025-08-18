#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking session storage for demonstration purposes
typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session current_session = {"user123", "user@example.com", "123-45-6789"};

void info() {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\nEmail: %s\nSSN: %s\n",
           current_session.username,
           current_session.email,
           current_session.ssn);
}

int main() {
    char request_line[256];

    // Simulating a web server accepting input
    printf("Enter the HTTP request (e.g., GET /info HTTP/1.1):\n");
    fgets(request_line, sizeof(request_line), stdin);

    if (strncmp(request_line, "GET /info", 9) == 0) {
        info();
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }

    return 0;
}