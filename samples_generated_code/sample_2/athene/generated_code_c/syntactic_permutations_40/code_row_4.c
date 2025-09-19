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
    Session *session = malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
    return session;
}

void info(Session *session) {
    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: text/html\n\n");

    printf("<html>\n");
    printf("<head><title>User Info</title></head>\n");
    printf("<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", session->username);
    printf("<p>Email: %s</p>\n", session->email);
    if (strlen(session->ssn) >= 4) {
        printf("<p>Last 4 digits of SSN: %.*s</p>\n", 4, session->ssn + strlen(session->ssn) - 4);
    }
    printf("</body>\n");
    printf("</html>\n");
}

int main() {
    // Simulate a session with some data
    Session *session = create_session("user123", "user@example.com", "123-45-6789");

    // Simulate the /info route being accessed
    info(session);

    // Clean up
    free_session(session);
    return 0;
}