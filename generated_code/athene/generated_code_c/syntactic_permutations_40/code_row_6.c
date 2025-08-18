#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

void init_session(char *username, char *email, char *ssn) {
    session = (Session *)malloc(sizeof(Session));
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* get_last_4_digits(const char *ssn) {
    if (strlen(ssn) < 4) return NULL;
    char *last_4 = (char *)malloc(5 * sizeof(char));
    strncpy(last_4, ssn + strlen(ssn) - 4, 4);
    last_4[4] = '\0';
    return last_4;
}

void info() {
    if (!session || !session->username || !session->email || !session->ssn) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Session data missing</body></html>");
        return;
    }

    char *last_4_ssn = get_last_4_digits(session->ssn);
    if (!last_4_ssn) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Invalid SSN</body></html>");
        return;
    }

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_4_ssn);
    printf("</body></html>");

    free(last_4_ssn);
}

int main() {
    // Initialize session with some test data
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate a GET request to /info
    info();

    // Clean up
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);

    return 0;
}