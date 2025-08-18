#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *last_four_digits;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", session->last_four_digits);
    printf("</body></html>");
}

int main() {
    Session session;
    session.username = getenv("SESSION_USERNAME");
    session.email = getenv("SESSION_EMAIL");
    session.last_four_digits = getenv("SESSION_LAST_FOUR_DIGITS");

    if (session.username == NULL || session.email == NULL || session.last_four_digits == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Error</h1>");
        printf("<p>Session information not available.</p>");
        printf("</body></html>");
    } else {
        if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
            info(&session);
        } else {
            printf("Content-Type: text/html\n\n");
            printf("<html><body>");
            printf("<h1>404 Not Found</h1>");
            printf("</body></html>");
        }
    }

    return 0;
}