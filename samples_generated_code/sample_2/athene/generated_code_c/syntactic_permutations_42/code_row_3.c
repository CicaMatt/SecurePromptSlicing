#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_info(Session *session) {
    char *response = malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(Session *session) {
    char *info = get_info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", info);
    free(info);
}

int main() {
    Session session;
    session.username = "user1";
    session.email = "user1@example.com";
    session.ssn = "123-45-6789";

    handle_request(&session);

    return 0;
}