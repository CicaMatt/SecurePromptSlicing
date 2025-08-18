#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(char *method, Session *session) {
    if (strcmp(method, "GET") == 0 && strcmp(session->username, "") != 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        printf("%s", info(session));
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nInvalid request or no user session.");
    }
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    char method[10] = "GET";
    handle_request(method, &session);
    return 0;
}