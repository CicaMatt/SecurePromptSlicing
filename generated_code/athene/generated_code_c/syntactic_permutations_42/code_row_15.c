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

char *info(Session *session) {
    char *response = NULL;
    int len = asprintf(&response, "Username: %s\nEmail: %s\nSSN: %s", 
                       session->username, session->email, session->ssn);
    if (len < 0) {
        return NULL;
    }
    return response;
}

int main() {
    // Simulate a user session
    Session *session = create_session("user123", "user123@example.com", "123-45-6789");

    // Route handler for /info
    char *response = info(session);
    if (response) {
        printf("%s\n", response);
        free(response);
    }

    // Clean up session
    free_session(session);

    return 0;
}