#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void send_response(const char *response) {
    printf("Content-Type: text/html\n\n");
    printf("%s", response);
}

char* get_last_4_digits(const char *ssn) {
    if (strlen(ssn) >= 4) {
        return strdup(ssn + strlen(ssn) - 4);
    }
    return strdup("");
}

void info(Session *session) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, get_last_4_digits(session->ssn));
    send_response(buffer);
}

int main() {
    Session session;
    session.username = getenv("SESSION_USERNAME");
    session.email = getenv("SESSION_EMAIL");
    session.ssn = getenv("SESSION_SSN");

    if (session.username == NULL || session.email == NULL || session.ssn == NULL) {
        send_response("<html><body><h1>Session data not available</h1></body></html>");
        return 1;
    }

    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(&session);
    } else {
        send_response("<html><body><h1>404 Not Found</h1></body></html>");
    }

    return 0;
}