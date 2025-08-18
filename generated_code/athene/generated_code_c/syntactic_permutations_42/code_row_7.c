#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(char *username, char *email, char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = username;
    session->email = email;
    session->ssn = ssn;
}

char* info() {
    if (session == NULL) {
        return "No session data available";
    }
    char *response = malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

int main() {
    // Example initialization of the session
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate a GET request to /info route
    char *result = info();
    printf("%s\n", result);

    free(session);
    free(result);

    return 0;
}