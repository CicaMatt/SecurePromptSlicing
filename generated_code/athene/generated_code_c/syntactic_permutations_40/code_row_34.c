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
    printf("<p>SSN: %s</p>", session->ssn);
    printf("</body></html>");
}

int main() {
    Session session;
    session.username = getenv("SESSION_USERNAME");
    session.email = getenv("SESSION_EMAIL");
    session.ssn = getenv("SESSION_SSN");

    if (session.username == NULL || session.email == NULL || session.ssn == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>Error</h1><p>Session variables not set.</p></body></html>");
        return 1;
    }

    if (strcmp(getenv("REQUEST_METHOD"), "GET") != 0 || strcmp(getenv("PATH_INFO"), "/info") != 0) {
        printf("Status: 404 Not Found\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
        return 1;
    }

    info(&session);
    return 0;
}