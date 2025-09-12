#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn_last_4);
    free(session);
}

Session *create_session(const char *username, const char *email, const char *ssn) {
    Session *session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn_last_4 = strdup(ssn + strlen(ssn) - 4);
    return session;
}

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", session->ssn_last_4);
    printf("</body></html>");
}

int main() {
    // Simulate a session with dummy data
    Session *session = create_session("john_doe", "john.doe@example.com", "123-45-6789");

    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(session);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Not Found");
    }

    free_session(session);
    return 0;
}