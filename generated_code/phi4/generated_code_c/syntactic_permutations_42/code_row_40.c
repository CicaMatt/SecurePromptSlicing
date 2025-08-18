#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char username[256];
    char email[256];
    char ssn[20];
} Session;

Session session;

void set_session(const char *key, const char *value) {
    if (strcmp(key, SESSION_USERNAME) == 0) {
        strncpy(session.username, value, sizeof(session.username));
    } else if (strcmp(key, SESSION_EMAIL) == 0) {
        strncpy(session.email, value, sizeof(session.email));
    } else if (strcmp(key, SESSION_SSN) == 0) {
        strncpy(session.ssn, value, sizeof(session.ssn));
    }
}

char* get_info() {
    static char info[1024];
    snprintf(info, sizeof(info), "Username: %s\nEmail: %s\nSSN: %s", 
             session.username, session.email, session.ssn);
    return info;
}

void handle_request(const char *request) {
    if (strcmp(request, "/info") == 0) {
        printf("200 OK\n");
        printf("%s\n", get_info());
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate setting session variables
    set_session(SESSION_USERNAME, "john_doe");
    set_session(SESSION_EMAIL, "john.doe@example.com");
    set_session(SESSION_SSN, "123-45-6789");

    // Simulate handling a request to the /info route
    handle_request("/info");

    return 0;
}