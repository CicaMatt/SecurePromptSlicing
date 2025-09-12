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

Session session;

void set_session(const char *key, const char *value) {
    if (strcmp(key, SESSION_USERNAME) == 0) {
        free(session.username);
        session.username = strdup(value);
    } else if (strcmp(key, SESSION_EMAIL) == 0) {
        free(session.email);
        session.email = strdup(value);
    } else if (strcmp(key, SESSION_SSN) == 0) {
        free(session.ssn);
        session.ssn = strdup(value);
    }
}

char* get_session(const char *key) {
    if (strcmp(key, SESSION_USERNAME) == 0) return session.username;
    if (strcmp(key, SESSION_EMAIL) == 0) return session.email;
    if (strcmp(key, SESSION_SSN) == 0) return session.ssn;
    return NULL;
}

void free_session() {
    free(session.username);
    free(session.email);
    free(session.ssn);
}

void info(void (*response_func)(const char*)) {
    const char *username = get_session(SESSION_USERNAME);
    const char *email = get_session(SESSION_EMAIL);
    const char *ssn = get_session(SESSION_SSN);

    if (username == NULL || email == NULL || ssn == NULL) {
        response_func("Missing session data");
        return;
    }

    char ssn_last_four[5];
    strncpy(ssn_last_four, &ssn[strlen(ssn)-4], 4);
    ssn_last_four[4] = '\0';

    char *response_body = malloc(512);
    snprintf(response_body, 512,
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             username, email, ssn_last_four);

    response_func(response_body);
    free(response_body);
}

void send_response(const char *response) {
    printf("Content-Type: text/html\n\n");
    printf("%s", response);
}

int main() {
    set_session(SESSION_USERNAME, "JohnDoe");
    set_session(SESSION_EMAIL, "john.doe@example.com");
    set_session(SESSION_SSN, "123-45-6789");

    // Simulating a request to /info
    info(send_response);

    free_session();
    return 0;
}