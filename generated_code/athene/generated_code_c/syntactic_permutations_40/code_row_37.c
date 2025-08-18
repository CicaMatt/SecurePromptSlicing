#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void send_response(const char *content) {
    printf("Content-Type: text/html\n\n");
    printf("%s", content);
}

char* get_last_four(const char *ssn) {
    static char last_four[5];
    strncpy(last_four, ssn + strlen(ssn) - 4, 4);
    last_four[4] = '\0';
    return last_four;
}

void info(Session *session) {
    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "Username: %s<br>"
             "Email: %s<br>"
             "Last 4 digits of SSN: %s"
             "</body></html>",
             session->username, session->email, get_last_four(session->ssn));
    send_response(response);
}

int main() {
    Session session = {"user123", "user@example.com", "123-45-6789"};
    info(&session);
    return 0;
}