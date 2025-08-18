#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* info() {
    if (session == NULL) return "User not logged in";

    char *response = malloc(1024);
    snprintf(response, 1024, "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
             session->username, session->email, session->ssn);
    return response;
}

void handle_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        char *response = info();
        printf("HTTP/1.1 200 OK\nContent-Type: application/json\n\n%s\n", response);
        free(response);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nRoute not found.\n");
    }
}

int main() {
    session = malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    handle_request("/info");

    free(session);
    return 0;
}