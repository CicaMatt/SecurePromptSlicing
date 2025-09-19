#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    session = malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    char *request_path = "/info"; // Simulate a request to /info
    handle_request(request_path);

    free(session);
    return 0;
}