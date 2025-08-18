#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", session->username);
    printf("Email: %s\n", session->email);
    printf("SSN: %s\n", session->ssn);
}

void handle_request(char *path, Session *session) {
    if (strcmp(path, "/info") == 0) {
        info(session);
    } else {
        printf("HTTP/1.1 404 Not Found\n");
        printf("Content-Type: text/plain\n\n");
        printf("Not Found\n");
    }
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john@example.com",
        .ssn = "123-45-6789"
    };

    char *request_path = "/info"; // Simulate a request to /info
    handle_request(request_path, &session);

    return 0;
}