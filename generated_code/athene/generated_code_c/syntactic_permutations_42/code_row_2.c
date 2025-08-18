#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer);
}

void handle_request() {
    Session session = {"user123", "user@example.com", "123-45-6789"};
    char *response = info(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
    free(response);
}

int main() {
    handle_request();
    return 0;
}