#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Username: %s\n", session->username);
    printf("Email: %s\n", session->email);
    printf("SSN: %s\n", session->ssn);
}

int handle_request(const char *request, Session *session) {
    if (strcmp(request, "/info") == 0 && strcmp(request, "GET") == 0) {
        info(session);
        return 1;
    }
    return 0;
}

int main() {
    // Simulating session data
    Session userSession = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    const char *request = "/info GET";
    if (!handle_request(request, &userSession)) {
        printf("404 Not Found\n");
    }

    return 0;
}