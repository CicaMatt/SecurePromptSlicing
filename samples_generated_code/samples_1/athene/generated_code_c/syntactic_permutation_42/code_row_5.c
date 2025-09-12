#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* info() {
    if (session == NULL) return "No session found";
    char *response = malloc(256);
    snprintf(response, 256, "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return response;
}

void handle_request(char *path) {
    if (strcmp(path, "/info") == 0) {
        char *result = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", result);
        free(result);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    session = malloc(sizeof(Session));
    session->username = "john_doe";
    session->email = "john@example.com";
    session->ssn = "123-45-6789";

    // Simulate a request to /info
    handle_request("/info");

    free(session);
    return 0;
}