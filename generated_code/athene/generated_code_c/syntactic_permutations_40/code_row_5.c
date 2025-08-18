#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
}

char* info(Session *session) {
    const int buffer_size = 256;
    char *response = malloc(buffer_size * sizeof(char));
    snprintf(response, buffer_size, 
             "Username: %s<br>Email: %s<br>Last 4 digits of SSN: %s",
             session->username, session->email, &session->ssn[strlen(session->ssn) - 4]);
    return response;
}

int main() {
    // Simulate a web request
    Session *session = malloc(sizeof(Session));
    session->username = strdup("user123");
    session->email = strdup("user123@example.com");
    session->ssn = strdup("123-45-6789");

    char *response = info(session);
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s\n", response);

    free(response);
    free_session(session);
    free(session);

    return 0;
}