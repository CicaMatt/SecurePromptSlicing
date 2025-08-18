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

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    if (strlen(session->ssn) >= 4) {
        char last_4[5];
        strncpy(last_4, session->ssn + strlen(session->ssn) - 4, 4);
        last_4[4] = '\0';
        printf("<p>Last 4 digits of SSN: %s</p>", last_4);
    } else {
        printf("<p>Last 4 digits of SSN: Not available</p>");
    }
    printf("</body></html>\n");
}

int main() {
    // Simulate a session with some user data
    Session *session = create_session("user123", "user123@example.com", "123-45-6789");

    // Handle the /info route
    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(session);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found\n");
    }

    free_session(session);
    return 0;
}