#include <stdio.h>
#include <stdlib.h>

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

char *info() {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return buffer;
}

int main() {
    // Example initialization of the session
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate a GET request to /info
    char *response = info();
    printf("%s\n", response);

    // Clean up
    free_session();

    return 0;
}