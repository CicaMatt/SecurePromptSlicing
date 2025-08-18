#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *key;
    char *value;
} Session;

Session* create_session(const char *key, const char *value) {
    Session *session = (Session *)malloc(sizeof(Session));
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

typedef struct {
    Session **sessions;
    size_t count;
} SessionManager;

SessionManager* create_session_manager() {
    SessionManager *manager = (SessionManager *)malloc(sizeof(SessionManager));
    manager->sessions = NULL;
    manager->count = 0;
    return manager;
}

void add_session(SessionManager *manager, Session *session) {
    manager->sessions = realloc(manager->sessions, sizeof(Session*) * (manager->count + 1));
    manager->sessions[manager->count++] = session;
}

Session* get_session(const SessionManager *manager, const char *key) {
    for (size_t i = 0; i < manager->count; ++i) {
        if (strcmp(manager->sessions[i]->key, key) == 0) {
            return manager->sessions[i];
        }
    }
    return NULL;
}

void free_session_manager(SessionManager *manager) {
    for (size_t i = 0; i < manager->count; ++i) {
        free_session(manager->sessions[i]);
    }
    free(manager->sessions);
    free(manager);
}

char* info(const SessionManager *sessionManager) {
    static char response[256];
    const char *username = get_session(sessionManager, SESSION_USERNAME)->value;
    const char *email = get_session(sessionManager, SESSION_EMAIL)->value;
    const char *ssn = get_session(sessionManager, SESSION_SSN)->value;

    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", username, email, ssn);
    return response;
}

void handle_request(const SessionManager *sessionManager) {
    if (strcmp("/info", "/info") == 0) { // Simulating a GET request to /info
        printf("Response from /info:\n%s\n", info(sessionManager));
    }
}

int main() {
    SessionManager *sessionManager = create_session_manager();
    
    add_session(sessionManager, create_session(SESSION_USERNAME, "john_doe"));
    add_session(sessionManager, create_session(SESSION_EMAIL, "john@example.com"));
    add_session(sessionManager, create_session(SESSION_SSN, "123-45-6789"));

    handle_request(sessionManager);

    free_session_manager(sessionManager);
    
    return 0;
}