#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

void send_response(const char *content) {
    printf("Content-Type: text/html\n\n");
    printf("%s", content);
}

void info(Session *session) {
    char response[256];
    snprintf(response, sizeof(response), 
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last_4);
    send_response(response);
}

int main() {
    Session session = {"john_doe", "john@example.com", "1234"};
    info(&session);
    return 0;
}