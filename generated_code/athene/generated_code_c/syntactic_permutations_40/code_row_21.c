#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void free_session(Session *session) {
    free(session->username);
    free(session->email);
    free(session->ssn);
}

char* get_last_four(const char *ssn) {
    char *last_four = (char *)malloc(5 * sizeof(char));
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void info(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    char *last_four = get_last_four(session->ssn);
    printf("<p>Last 4 digits of SSN: %s</p>", last_four);
    free(last_four);
    printf("</body></html>");
}

int main() {
    Session session;
    session.username = strdup("john_doe");
    session.email = strdup("john@example.com");
    session.ssn = strdup("123-45-6789");

    if (strcmp("GET", getenv("REQUEST_METHOD")) == 0 && strcmp("/info", getenv("PATH_INFO")) == 0) {
        info(&session);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("404 Not Found");
    }

    free_session(&session);
    return 0;
}