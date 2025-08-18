#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char response[256];
    snprintf(response, sizeof(response), "Username: %s; Email: %s; SSN: %s", session->username, session->email, session->ssn);
    return strdup(response);
}

void handle_request(Session *session) {
    printf("Content-Type: text/plain\n\n");
    printf("%s", info(session));
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    handle_request(&session);
    return 0;
}