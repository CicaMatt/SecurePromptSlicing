#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void send_response(const char *response) {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", response);
}

char* get_last_four_digits(const char *ssn) {
    char *last_four = malloc(5 * sizeof(char));
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void handle_info_route(Session *session) {
    if (!session || !session->username || !session->email || !session->ssn) {
        send_response("<h1>Session not initialized</h1>");
        return;
    }

    char *last_four_ssn = get_last_four_digits(session->ssn);
    char response[256];
    snprintf(response, sizeof(response), "<html><body><h1>User Info</h1><p>Username: %s</p><p>Email: %s</p><p>Last 4 digits of SSN: %s</p></body></html>", session->username, session->email, last_four_ssn);
    free(last_four_ssn);

    send_response(response);
}

int main() {
    // Simulate a session
    Session session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123456789"
    };

    handle_info_route(&session);

    return 0;
}