#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer); // Return a duplicate of the string to avoid returning a local variable
}

int main() {
    Session *session = (Session *)malloc(sizeof(Session));
    if (!session) exit(1);

    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    char *response = info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);

    free(response);
    free(session);

    return 0;
}