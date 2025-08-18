#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *ssn;
} Session;

void send_response(const char* content) {
    printf("Content-Type: text/html\n\n");
    printf("%s", content);
}

void info(Session *session) {
    if (session == NULL || session->username == NULL || session->ssn == NULL) {
        send_response("<h1>Session data not available</h1>");
        return;
    }
    char response[256];
    snprintf(response, sizeof(response), "<html><body><p>Username: %s</p><p>Last 4 digits of SSN: %s</p></body></html>", session->username, session->ssn + strlen(session->ssn) - 4);
    send_response(response);
}

int main() {
    Session session;
    session.username = "john_doe";
    session.ssn = "123-45-6789";

    if (strcmp("GET", getenv("REQUEST_METHOD")) == 0 && strcmp("/info", getenv("PATH_INFO")) == 0) {
        info(&session);
    } else {
        send_response("<h1>Not Found</h1>");
    }

    return 0;
}