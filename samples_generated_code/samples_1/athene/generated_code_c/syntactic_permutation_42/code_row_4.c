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
    return strdup(buffer);
}

int main() {
    Session session = { .username = "user123", .email = "user@example.com", .ssn = "123-45-6789" };
    char *response = info(&session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
    free(response);
    return 0;
}