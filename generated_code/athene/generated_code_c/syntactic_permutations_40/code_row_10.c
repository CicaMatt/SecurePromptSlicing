#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session *session = NULL;

char* get_last_four(const char *ssn) {
    if (strlen(ssn) < 4) return "XXXX";
    char *last_four = malloc(5);
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void info() {
    printf("Content-Type: text/html\n\n");
    if (session == NULL) {
        printf("<h1>No session data available</h1>");
        return;
    }
    char *last_four_ssn = get_last_four(session->ssn);
    printf("<html><body>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_four_ssn);
    printf("</body></html>");
    free(last_four_ssn);
}

int main() {
    // Example session initialization (in a real app, this would come from the session management)
    session = malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user@example.com";
    session->ssn = "123-45-6789";

    // Simulate handling of /info route
    info();

    free(session);
    return 0;
}