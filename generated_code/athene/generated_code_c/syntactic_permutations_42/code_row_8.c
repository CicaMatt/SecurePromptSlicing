#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session;

char* info() {
    if (session == NULL) {
        return "Session not initialized";
    }
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer); // Return a dynamically allocated string
}

int main() {
    // Simulate a session with some user data
    session = (Session *)malloc(sizeof(Session));
    if (session == NULL) {
        perror("Failed to allocate memory for session");
        exit(1);
    }
    session->username = "john_doe";
    session->email = "john.doe@example.com";
    session->ssn = "123-45-6789";

    // Simulate a GET request to /info
    char *response = info();
    printf("%s\n", response);
    free(response); // Free the dynamically allocated string

    // Clean up
    free(session);
    return 0;
}