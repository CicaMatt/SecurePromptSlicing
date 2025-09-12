#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(char *username, char *email, char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* info() {
    if (session == NULL) return "No session data available";
    char *response = malloc(1024);
    sprintf(response, "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

void handle_request(char *method, char *path) {
    if (strcmp(method, "GET") == 0 && strcmp(path, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    init_session("user1", "user1@example.com", "123-45-6789");
    handle_request("GET", "/info");
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
    return 0;
}