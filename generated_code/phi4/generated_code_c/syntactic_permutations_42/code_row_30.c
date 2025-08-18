#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_KEY_USERNAME "username"
#define SESSION_KEY_EMAIL "email"
#define SESSION_KEY_SSN "ssn"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void init_session(Session *session, const char *username, const char *email, const char *ssn) {
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn);
}

const char* info(const Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Email: %s, SSN: %s", session->email, session->ssn);
    return response;
}

void handle_request(const char *route, const Session *session) {
    if (strcmp(route, "/info") == 0) {
        printf("%s\n", info(session));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate session data
    Session session;
    init_session(&session, "john_doe", "john.doe@example.com", "123-45-6789");

    // Simulate a request to the /info route
    handle_request("/info", &session);

    free_session(&session);
    return 0;
}