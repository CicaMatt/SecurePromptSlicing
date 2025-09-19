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
    if (session == NULL) return "No session found";

    static char response[256];
    snprintf(response, sizeof(response), 
             "Username: %s\nEmail: %s\nSSN: %s", 
             session->username, session->email, session->ssn);
    return response;
}

int main() {
    // Example initialization of the session
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate a GET request to /info
    printf("%s\n", info());

    free(session);
    return 0;
}