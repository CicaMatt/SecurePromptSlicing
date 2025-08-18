#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void init_session(Session *session, const char *username, const char *email, const char *ssn) {
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* info(Session *session) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer);
}

int main() {
    Session session;
    init_session(&session, "user123", "user@example.com", "123-45-6789");

    char *response = info(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
    printf("%s", response);

    free(session.username);
    free(session.email);
    free(session.ssn);
    free(response);

    return 0;
}