#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(char *username, char *email, char *ssn) {
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

void handle_info_request() {
    if (session == NULL) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>No session found.</body></html>");
        return;
    }

    char ssn_last4[5];
    strncpy(ssn_last4, session->ssn + strlen(session->ssn) - 4, 4);
    ssn_last4[4] = '\0';

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn_last4);
    printf("</body></html>");
}

int main() {
    // Example initialization of session (in a real app, this would come from an authenticated user)
    init_session("user123", "user@example.com", "123-45-6789");

    handle_info_request();

    free_session();
    return 0;
}