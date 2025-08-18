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

int handle_request(char *route) {
    if (strcmp(route, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n%s", response);
        free(response);
        return 0;
    }
    printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found");
    return -1;
}

int main() {
    session = (Session *)malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    char *request_route = "/info"; // Simulating a GET request to /info
    handle_request(request_route);

    free(session);
    return 0;
}