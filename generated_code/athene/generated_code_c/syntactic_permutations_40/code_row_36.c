#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    printf("<p>SSN: %s</p>", session->ssn);
    printf("</body></html>");
}

int main() {
    Session session = {"user123", "user@example.com", "123-45-6789"};

    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        info(&session);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Method not allowed");
    }

    return 0;
}