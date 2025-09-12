#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(const char *username, const char *email, const char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char *info() {
    if (session == NULL) return "No session data available";
    char *response = malloc(256);
    snprintf(response, 256, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", 
             session->username, session->email, session->ssn);
    return response;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n");
        char *response = info();
        printf("%s", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    init_session("user123", "user@example.com", "123-45-6789");

    char *request = "/info";
    handle_request(request);

    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);

    return 0;
}