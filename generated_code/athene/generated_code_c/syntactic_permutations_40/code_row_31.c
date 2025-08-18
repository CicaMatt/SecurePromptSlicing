#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", session->username);
    printf("Email: %s\n", session->email);
    char last4[5];
    strncpy(last4, &session->ssn[strlen(session->ssn) - 4], 4);
    last4[4] = '\0';
    printf("Last 4 of SSN: %s\n", last4);
}

int main() {
    Session session;
    session.username = "john_doe";
    session.email = "john.doe@example.com";
    session.ssn = "123-45-6789";

    // Simulate a web request to /info
    info(&session);

    return 0;
}