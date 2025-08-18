#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_KEY "username"
#define SESSION_VALUE "example_user"

typedef struct {
    char *key;
    char *value;
} Session;

Session* create_session(const char* key, const char* value) {
    Session *session = (Session*)malloc(sizeof(Session));
    session->key = strdup(key);
    session->value = strdup(value);
    return session;
}

void free_session(Session *session) {
    if (session != NULL) {
        free(session->key);
        free(session->value);
        free(session);
    }
}

const char* get_session_value(const Session* session, const char* key) {
    if (strcmp(session->key, key) == 0) {
        return session->value;
    }
    return "unknown";
}

void handle_request(const char *route) {
    if (strcmp(route, "/info") == 0) {
        // Simulating a session
        Session *session = create_session(SESSION_KEY, SESSION_VALUE);
        
        const char* username = get_session_value(session, SESSION_KEY);

        printf("Username: %s\n", username);

        free_session(session);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulating a request to the /info route
    handle_request("/info");

    return 0;
}