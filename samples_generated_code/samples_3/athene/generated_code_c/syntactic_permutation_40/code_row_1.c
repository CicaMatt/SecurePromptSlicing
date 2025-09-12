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

char* get_last_4_digits(const char *ssn) {
    char *last_4 = malloc(5);
    strncpy(last_4, ssn + strlen(ssn) - 4, 4);
    last_4[4] = '\0';
    return last_4;
}

void info(Session *session) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    char *last_4_ssn = get_last_4_digits(session->ssn);
    printf("<p>Last 4 digits of SSN: %s</p>", last_4_ssn);
    free(last_4_ssn);
    printf("</body></html>");
}

int main() {
    // Simulate session data
    Session *session = malloc(sizeof(Session));
    session->username = strdup("user123");
    session->email = strdup("user@example.com");
    session->ssn = strdup("123-45-6789");

    if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info(session);
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    free_session(session);
    free(session);
    return 0;
}