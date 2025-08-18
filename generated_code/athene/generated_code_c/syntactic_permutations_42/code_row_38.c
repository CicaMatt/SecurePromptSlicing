#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* email;
    char* ssn;
} Session;

void info(Session* session, char* response) {
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
}

int main() {
    // Simulate a session
    Session session = {
        .username = "user123",
        .email = "user123@example.com",
        .ssn = "123-45-6789"
    };

    char response[256];
    info(&session, response);

    // Simulate the HTTP GET /info route
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n");
    printf("\n");
    printf("%s\n", response);

    return 0;
}