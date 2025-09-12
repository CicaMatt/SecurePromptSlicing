#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* info() {
    if (session == NULL) return "No user session found.";
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", 
             session->username, session->email, session->ssn);
    return response;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
        puts(info());
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        puts("Not Found");
    }
}

int main() {
    session = (Session *)malloc(sizeof(Session));
    if (session == NULL) return -1;

    // Example session data
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    // Simulate a request to /info
    handle_request("/info");

    free(session);
    return 0;
}