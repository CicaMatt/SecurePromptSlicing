#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void set_session(Session *session, const char *key, const char *value) {
    if (strcmp(key, SESSION_USERNAME) == 0) {
        session->username = strdup(value);
    } else if (strcmp(key, SESSION_EMAIL) == 0) {
        session->email = strdup(value);
    } else if (strcmp(key, SESSION_SSN) == 0) {
        session->ssn = strdup(value);
    }
}

char *get_session_info(const Session *session) {
    char *info = malloc(256);
    snprintf(info, 256, "Username: %s\nEmail: %s\nSSN: %s", 
             session->username ? session->username : "Not set",
             session->email ? session->email : "Not set",
             session->ssn ? session->ssn : "Not set");
    return info;
}

void handle_request(const char *route, Session *session) {
    if (strcmp(route, "/info") == 0) {
        printf("%s", get_session_info(session));
    } else {
        printf("Route not found\n");
    }
}

int main() {
    // Simulate setting session variables
    Session session = {0};
    set_session(&session, SESSION_USERNAME, "john_doe");
    set_session(&session, SESSION_EMAIL, "john.doe@example.com");
    set_session(&session, SESSION_SSN, "123-45-6789");

    // Handle a request to /info
    handle_request("/info", &session);

    // Free allocated memory
    free(session.username);
    free(session.email);
    free(session.ssn);

    return 0;
}