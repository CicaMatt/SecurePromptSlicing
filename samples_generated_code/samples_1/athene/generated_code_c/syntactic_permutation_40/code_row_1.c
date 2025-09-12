#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    if (session->username) free(session->username);
    if (session->email) free(session->email);
    if (session->ssn) free(session->ssn);
}

char* get_last_four(const char *ssn) {
    char *last_four = malloc(5);
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void info(Session *session) {
    if (session == NULL || session->username == NULL || session->email == NULL || session->ssn == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n");
        printf("<h1>Session data missing</h1>");
    } else {
        char *last_four = get_last_four(session->ssn);
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<p>Username: %s</p>", session->username);
        printf("<p>Email: %s</p>", session->email);
        printf("<p>Last 4 digits of SSN: %s</p>", last_four);
        printf("</body></html>");
        free(last_four);
    }
}

int main() {
    // Simulate a session with some data
    Session session;
    session.username = strdup("user123");
    session.email = strdup("user123@example.com");
    session.ssn = strdup("123-45-6789");

    info(&session);

    free_session(&session);
    return 0;
}