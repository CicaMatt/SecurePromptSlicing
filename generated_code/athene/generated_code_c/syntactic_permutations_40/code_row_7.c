#include <stdio.h>
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
    int len = strlen(ssn);
    if (len < 4) return ssn;
    char *last_4 = (char *)malloc(5);
    strncpy(last_4, &ssn[len - 4], 4);
    last_4[4] = '\0';
    return last_4;
}

void info() {
    if (!session) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Session not initialized</h1></body></html>");
        return;
    }

    char *last_4_ssn = get_last_4_digits(session->ssn);
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_4_ssn);
    printf("</body></html>");
    free(last_4_ssn);
}

int main() {
    // Example initialization of session (in a real application, this would be set by the server)
    init_session("user123", "user@example.com", "123-45-6789");

    // Simulate a request to /info
    info();

    // Clean up
    free(session->username);
    free(session->email);
    free(session->ssn);
    free(session);

    return 0;
}