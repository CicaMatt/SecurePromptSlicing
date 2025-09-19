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

char *info() {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn + strlen(session->ssn) - 4);
    return strdup(buffer);
}

int main() {
    // Simulate a session with test data
    init_session("john_doe", "john@example.com", "123-45-6789");

    // Simulate a GET request to /info
    char *response = info();
    printf("%s\n", response);

    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
    free(response);

    return 0;
}