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

char* info() {
    if (session == NULL) return "No session found";
    int len = strlen(session->username) + strlen(session->email) + strlen(session->ssn) + 30;
    char *response = malloc(len);
    snprintf(response, len, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
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

int main() {
    init_session("user1", "user1@example.com", "123-45-6789");
    
    char *response = info();
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
    free(response);

    free_session();
    return 0;
}