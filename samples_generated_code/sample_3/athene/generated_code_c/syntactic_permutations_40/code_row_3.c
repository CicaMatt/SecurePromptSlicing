#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    if (strlen(session->ssn) >= 4) {
        printf("<p>Last 4 digits of SSN: %s</p>", session->ssn + strlen(session->ssn) - 4);
    } else {
        printf("<p>Last 4 digits of SSN: Not enough digits provided</p>");
    }
    printf("</body></html>");
}

int main() {
    // Simulate a session
    Session session;
    session.username = "john_doe";
    session.email = "john.doe@example.com";
    session.ssn = "123456789";

    // Simulate a GET request to /info
    info(&session);

    return 0;
}