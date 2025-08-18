#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void handle_request(Session *session) {
    if (strcmp("/info", "/info") == 0 && strcmp("GET", "GET") == 0) {
        info(session);
    }
}

char* info(Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session->username, session->email, session->ssn);
    return response;
}

int main() {
    Session session = {
        .username = "user123",
        .email = "user@example.com",
        .ssn = "123-45-6789"
    };

    handle_request(&session);

    printf("%s\n", info(&session));

    return 0;
}