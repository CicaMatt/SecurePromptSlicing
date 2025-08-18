#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);
}

Session *create_session(const char *username, const char *email, const char *ssn) {
    Session *session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
    return session;
}

void send_response(const char *content) {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", content);
}

void info(Session *session) {
    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn + strlen(session->ssn) - 4);
    send_response(response);
}

int main() {
    // Simulate a session with predefined values
    Session *session = create_session("user123", "user@example.com", "123-45-6789");

    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(session);
    } else {
        send_response("<html><body>404 Not Found</body></html>");
    }

    free_session(session);
    return 0;
}