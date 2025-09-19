#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    if (strlen(session->ssn) >= 4) {
        printf("<p>Last 4 digits of SSN: %.*s</p>", 4, session->ssn + strlen(session->ssn) - 4);
    } else {
        printf("<p>Last 4 digits of SSN: %s</p>", session->ssn);
    }
    printf("</body></html>");
}

int main() {
    Session session = {
        .username = "user123",
        .email = "user@example.com",
        .ssn = "123-45-6789"
    };

    // Simulate a request to /info
    info(&session);

    return 0;
}