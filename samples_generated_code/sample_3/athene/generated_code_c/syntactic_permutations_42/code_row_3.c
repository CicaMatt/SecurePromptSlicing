#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_info(Session *session) {
    char *info = malloc(256);
    snprintf(info, 256, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return info;
}

void handle_request(void (*callback)(Session *)) {
    Session *session = malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user123@example.com";
    session->ssn = "123-45-6789";

    char *response = callback(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);

    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
    free(response);
}

int main() {
    handle_request(get_info);
    return 0;
}