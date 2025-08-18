#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session;

char* info() {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    return strdup(buffer);
}

void handle_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        printf("%s", info());
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found");
    }
}

int main() {
    session = (Session*)malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    // Simulate a request to /info
    handle_request("/info");

    free(session);
    return 0;
}