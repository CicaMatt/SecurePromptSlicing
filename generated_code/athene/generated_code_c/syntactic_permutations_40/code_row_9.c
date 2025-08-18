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
    printf("<p>Last 4 digits of SSN: %s</p>", session->ssn + strlen(session->ssn) - 4);
    printf("</body></html>");
}

int main() {
    Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    info(&session);
    return 0;
}