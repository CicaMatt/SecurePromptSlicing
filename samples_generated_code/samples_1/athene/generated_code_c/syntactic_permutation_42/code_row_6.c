#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer);
}

int handle_request(Session *session) {
    char *response = info(session);
    printf("Content-Type: text/plain\n\n");
    printf("%s", response);
    free(response);
    return 0;
}

int main() {
    Session session = {"user123", "user@example.com", "123-45-6789"};
    handle_request(&session);
    return 0;
}