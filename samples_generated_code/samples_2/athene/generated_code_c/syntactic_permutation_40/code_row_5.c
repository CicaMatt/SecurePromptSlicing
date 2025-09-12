#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", &session->ssn[strlen(session->ssn) - 4]);
    printf("</body></html>");
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    // Simulate a GET request to /info
    info(&session);

    return 0;
}