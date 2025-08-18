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
    char *response = malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

int main() {
    // Mocking a user session for demonstration
    session = (Session*)malloc(sizeof(Session));
    session->username = "user1";
    session->email = "user1@example.com";
    session->ssn = "123-45-6789";

    char *result = info();
    printf("GET /info: %s\n", result);
    free(result);
    free(session);

    return 0;
}