#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/plain\n\n");
    printf("Username: %s\n", session->username);
    printf("Email: %s\n", session->email);
    printf("SSN: %s\n", session->ssn);
}

int main() {
    Session session = {"john_doe", "john@example.com", "123-45-6789"};
    if (strcmp("/info", getenv("REQUEST_URI")) == 0 && strcmp("GET", getenv("REQUEST_METHOD")) == 0) {
        info(&session);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Not Found\n");
    }
    return 0;
}