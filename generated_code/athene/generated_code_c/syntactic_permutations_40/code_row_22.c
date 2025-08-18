#include <stdio.h>
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
        printf("<p>Last 4 digits of SSN: Not available</p>");
    }
    printf("</body></html>");
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123456789"
    };

    // Simulate a GET request to /info
    info(&session);

    return 0;
}