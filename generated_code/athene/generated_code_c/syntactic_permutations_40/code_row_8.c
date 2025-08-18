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
    printf("<p>Last 4 digits of SSN: %s</p>", session->ssn + strlen(session->ssn) - 4);
    printf("</body></html>");
}

void handle_request(char *path, Session *session) {
    if (strcmp(path, "/info") == 0) {
        info(session);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("404 Not Found");
    }
}

int main() {
    char path[1024];
    sscanf(getenv("REQUEST_URI"), "%s", path);

    Session session;
    session.username = getenv("SESSION_USERNAME");
    session.email = getenv("SESSION_EMAIL");
    session.ssn = getenv("SESSION_SSN");

    handle_request(path, &session);

    return 0;
}