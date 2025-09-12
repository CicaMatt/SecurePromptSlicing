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
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", &session->ssn[strlen(session->ssn) - 4]);
    printf("</body></html>");
}

int main() {
    Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    if (strcmp("/info", getenv("REQUEST_URI")) == 0 && strcmp("GET", getenv("REQUEST_METHOD")) == 0) {
        info(&session);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }
    return 0;
}