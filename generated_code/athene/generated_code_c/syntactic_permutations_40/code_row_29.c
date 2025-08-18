#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    if (session == NULL || session->username == NULL || session->email == NULL || session->ssn == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        printf("Session data missing or invalid.\r\n");
        return;
    }

    char last4[5];
    strncpy(last4, session->ssn + strlen(session->ssn) - 4, 4);
    last4[4] = '\0';

    printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
    printf("{\"username\": \"%s\", \"email\": \"%s\", \"last_4_ssn\": \"%s\"}", session->username, session->email, last4);
}

int main() {
    // Simulate a web request to /info
    Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    info(&session);

    return 0;
}