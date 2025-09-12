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
    if (session == NULL) return "Session not initialized";
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

int main() {
    init_session("user1", "user1@example.com", "123-45-6789");

    // Simulate a GET request to /info
    printf("%s\n", info());

    free(session);
    return 0;
}