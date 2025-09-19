#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session;

char* info() {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer);
}

void handle_request(const char *method) {
    if (strcmp(method, "GET") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", info());
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\n");
    }
}

int main() {
    session = (Session*)malloc(sizeof(Session));
    session->username = "user1";
    session->email = "user1@example.com";
    session->ssn = "123-45-6789";

    handle_request("GET");

    free(session);
    return 0;
}