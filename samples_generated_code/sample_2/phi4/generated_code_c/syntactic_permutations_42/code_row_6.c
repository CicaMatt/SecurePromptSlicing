#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate a basic web server with a single route using C

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = { "user123", "user@example.com", "123-45-6789" };

void handle_request(const char *request) {
    if (strncmp(request, "GET /info HTTP/1.1\r\n", 23) == 0) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("%s\n%s\n%s\n", session.username, session.email, session.ssn);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n");
        printf("Not Found\n");
    }
}

int main() {
    char buffer[256];
    
    // Simulate a client request
    strcpy(buffer, "GET /info HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");

    handle_request(buffer);

    return 0;
}