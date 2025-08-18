#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
}

Session *create_session(const char *username, const char *email, const char *ssn) {
    Session *session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
    return session;
}

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", (int)strlen(session->ssn) < 4 ? (int)strlen(session->ssn) : 4, &session->ssn[strlen(session->ssn) - 4]);
    printf("</body></html>");
}

void handle_request() {
    // Simulate session data
    Session *session = create_session("user123", "user@example.com", "123-45-6789");
    info(session);
    free_session(session);
}

int main() {
    handle_request();
    return 0;
}