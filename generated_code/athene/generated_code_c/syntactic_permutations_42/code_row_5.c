#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* info() {
    if (session == NULL) return "No user session found.";
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return strdup(buffer);
}

void init_session(char *username, char *email, char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = username;
    session->email = email;
    session->ssn = ssn;
}

int main() {
    // Example initialization of a session
    init_session("user1", "user1@example.com", "123-45-6789");

    // Simulating the /info route GET request
    char *response = info();
    printf("%s\n", response);
    free(response);

    return 0;
}