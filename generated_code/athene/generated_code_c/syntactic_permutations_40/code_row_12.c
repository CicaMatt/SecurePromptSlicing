#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(const char *username, const char *email, const char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

void free_session() {
    if (session != NULL) {
        free(session->username);
        free(session->email);
        free(session->ssn);
        free(session);
        session = NULL;
    }
}

void info() {
    if (session == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Session not initialized.</body></html>");
        return;
    }

    char last4ssn[5];
    strncpy(last4ssn, session->ssn + strlen(session->ssn) - 4, 4);
    last4ssn[4] = '\0';

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last4ssn);
    printf("</body></html>");
}

int main() {
    // Simulate initializing a session with user data
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate handling a GET request to the /info route
    info();

    // Clean up
    free_session();
    return 0;
}