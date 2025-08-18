#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* info(Session *session) {
    char *response = malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(Session *session) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
    char *info_response = info(session);
    printf("%s\n", info_response);
    free(info_response);
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    handle_request(&session);
    return 0;
}