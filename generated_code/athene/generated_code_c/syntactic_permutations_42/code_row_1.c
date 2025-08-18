#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void set_session(Session *session, const char *username, const char *email, const char *ssn) {
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* info(Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

int main() {
    Session session;
    set_session(&session, "user1", "user1@example.com", "123-45-6789");

    char *response = info(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);

    free(session.username);
    free(session.email);
    free(session.ssn);

    return 0;
}