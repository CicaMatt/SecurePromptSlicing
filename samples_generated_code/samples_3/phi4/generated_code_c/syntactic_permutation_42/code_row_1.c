#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_SIZE 1024

typedef struct {
    char username[64];
    char email[128];
    char ssn[20];
} Session;

Session session = {
    .username = "defaultUser",
    .email = "user@example.com",
    .ssn = "123-45-6789"
};

void set_session(const char *username, const char *email, const char *ssn) {
    strncpy(session.username, username, sizeof(session.username));
    session.username[sizeof(session.username) - 1] = '\0';
    
    strncpy(session.email, email, sizeof(session.email));
    session.email[sizeof(session.email) - 1] = '\0';

    strncpy(session.ssn, ssn, sizeof(session.ssn));
    session.ssn[sizeof(session.ssn) - 1] = '\0';
}

void handle_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        info();
    } else {
        printf("404 Not Found\n");
    }
}

void info() {
    char response[SESSION_SIZE];
    snprintf(response, sizeof(response),
             "Username: %s\n"
             "Email: %s\n"
             "SSN: %s",
             session.username,
             session.email,
             session.ssn);
    
    printf("200 OK\n");
    printf("Content-Type: text/plain\n\n");
    printf("%s", response);
}

int main() {
    // Simulate setting session variables
    set_session("john_doe", "john.doe@example.com", "987-65-4321");

    // Simulate a web request to /info
    handle_request("/info");

    return 0;
}