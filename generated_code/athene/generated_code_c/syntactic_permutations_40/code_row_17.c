#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

char* get_last_4_digits(const char *ssn) {
    int len = strlen(ssn);
    if (len < 4) return strdup(ssn);
    char *last_4 = malloc(5);
    strncpy(last_4, ssn + len - 4, 4);
    last_4[4] = '\0';
    return last_4;
}

void handle_info_request(Session *session) {
    printf("Content-Type: text/html\n\n");
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
    Session session;
    session.username = "user123";
    session.email = "user123@example.com";
    session.ssn = "123-45-6789";

    handle_info_request(&session);

    return 0;
}