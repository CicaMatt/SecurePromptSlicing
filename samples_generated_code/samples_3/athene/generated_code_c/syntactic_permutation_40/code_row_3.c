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

void handle_info_request(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %.*s</p>", (int)strlen(session->ssn) - 4, &session->ssn[7]);
    printf("</body></html>");
}

int main() {
    // Simulate a session with user data
    Session *session = create_session("john_doe", "john.doe@example.com", "123-45-6789");

    // Handle the /info GET request
    handle_info_request(session);

    // Clean up
    free_session(session);
    return 0;
}