#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char *response = (char *) malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(Session *session) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n");
    printf("\n");
    char *response = info(session);
    printf("%s", response);
    free(response);
}

int main() {
    Session session;
    session.username = "john_doe";
    session.email = "john.doe@example.com";
    session.ssn = "123-45-6789";

    handle_request(&session);

    return 0;
}