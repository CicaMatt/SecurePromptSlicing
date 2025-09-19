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

void handle_request(const char *path, Session *session) {
    if (strcmp(path, "/info") == 0) {
        char *response = info(session);
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nNot Found\n");
    }
}

int main() {
    Session session = {
        .username = "user123",
        .email = "user123@example.com",
        .ssn = "123-45-6789"
    };

    // Simulate a GET request to /info
    handle_request("/info", &session);

    return 0;
}