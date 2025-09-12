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
    printf("<p>Username: %s</p>", session ? session->username : "N/A");
    printf("<p>Email: %s</p>", session ? session->email : "N/A");
    if (session && strlen(session->ssn) >= 4) {
        char last_four[5];
        strncpy(last_four, session->ssn + strlen(session->ssn) - 4, 4);
        last_four[4] = '\0';
        printf("<p>Last 4 digits of SSN: %s</p>", last_four);
    }
    printf("</body></html>");
}

int main() {
    // Simulate a session with user data
    Session *session = create_session("user123", "user123@example.com", "123456789");

    // Call the info function to handle the /info route
    info(session);

    // Clean up the session
    free_session(session);
    return 0;
}