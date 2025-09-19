#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char *response = malloc(1024);
    snprintf(response, 1024, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(Session *session) {
    char *result = info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", result);
    free(result);
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    handle_request(&session);
    return 0;
}