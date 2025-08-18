#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SESSION_VARS 10

typedef struct {
    char key[50];
    char value[256];
} SessionVar;

typedef struct {
    int count;
    SessionVar vars[MAX_SESSION_VARS];
} Session;

Session session = {0};

void set_session_var(const char *key, const char *value) {
    if (session.count < MAX_SESSION_VARS) {
        strncpy(session.vars[session.count].key, key, sizeof(session.vars[session.count].key) - 1);
        strncpy(session.vars[session.count].value, value, sizeof(session.vars[session.count].value) - 1);
        session.count++;
    }
}

const char* get_session_var(const char *key) {
    for (int i = 0; i < session.count; i++) {
        if (strcmp(session.vars[i].key, key) == 0) {
            return session.vars[i].value;
        }
    }
    return NULL;
}

void handle_request() {
    const char* username = get_session_var("username");
    const char* email = get_session_var("email");
    const char* ssn = get_session_var("ssn");

    if (username && email && ssn) {
        printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\nUsername: %s\nEmail: %s\nSSN: %s", username, email, ssn);
    } else {
        printf("HTTP/1.1 400 Bad Request\nContent-Type: text/plain\n\nMissing session variables.");
    }
}

int main() {
    // Set up session variables
    set_session_var("username", "john_doe");
    set_session_var("email", "john.doe@example.com");
    set_session_var("ssn", "123-45-6789");

    // Simulate handling a request to /info
    printf("GET /info HTTP/1.1\nHost: localhost\n\n");
    handle_request();

    return 0;
}