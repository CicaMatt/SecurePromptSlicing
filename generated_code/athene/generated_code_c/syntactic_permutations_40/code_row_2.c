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
    Session *session = malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn + strlen(ssn) - 4); // Get last 4 digits of SSN
    return session;
}

void info(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", session->ssn);
    printf("</body></html>");
}

int main() {
    // Simulate a session
    Session *session = create_session("user123", "user@example.com", "123-45-6789");

    // Handle the /info route
    info(session);

    // Clean up
    free_session(session);
    return 0;
}