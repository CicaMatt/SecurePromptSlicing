#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* info() {
    if (session == NULL) return "No session data available";

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", 
             session->username, session->email, session->ssn);
    return strdup(buffer);
}

int main() {
    // Example of setting up a session
    session = (Session *) malloc(sizeof(Session));
    session->username = "user1";
    session->email = "user1@example.com";
    session->ssn = "123-45-6789";

    printf("Content-Type: application/json\n\n");
    printf("%s", info());

    free(session);
    return 0;
}