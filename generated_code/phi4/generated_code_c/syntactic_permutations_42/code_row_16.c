#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void set_session(Session *session, const char *username, const char *email, const char *ssn) {
    session->username = strdup(username);
    session->email = strdup(email);
    session->ssn = strdup(ssn);
}

char* info(const Session *session) {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", 
             session->username ? session->username : "None",
             session->email ? session->email : "None",
             session->ssn ? session->ssn : "None");
    return response;
}

int main() {
    Session user_session = {0};

    // Simulate setting session variables
    set_session(&user_session, "john_doe", "john@example.com", "123-45-6789");

    printf("Accessing /info route...\n");
    char *response = info(&user_session);
    printf("%s\n", response);

    // Free allocated memory
    free(user_session.username);
    free(user_session.email);
    free(user_session.ssn);

    return 0;
}