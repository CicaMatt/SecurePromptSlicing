#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void handle_request(char *route, Session *session) {
    if (strcmp(route, "/info") == 0) {
        char *response = info(session);
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found.\n");
    }
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john@example.com",
        .ssn = "123-45-6789"
    };

    char *route = "/info"; // Simulate a request to /info
    handle_request(route, &session);

    return 0;
}