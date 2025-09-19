#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "username"
#define SESSION_EMAIL "email"
#define SESSION_SSN "ssn"

typedef struct {
    char *key;
    char *value;
} SessionItem;

typedef struct {
    size_t count;
    SessionItem **items;
} Session;

Session* create_session() {
    Session *session = (Session*)malloc(sizeof(Session));
    session->count = 0;
    session->items = NULL;
    return session;
}

void free_session(Session *session) {
    if (!session) return;
    for (size_t i = 0; i < session->count; ++i) {
        free(session->items[i]->key);
        free(session->items[i]->value);
        free(session->items[i]);
    }
    free(session->items);
    free(session);
}

int set_session_item(Session *session, const char *key, const char *value) {
    for (size_t i = 0; i < session->count; ++i) {
        if (strcmp(session->items[i]->key, key) == 0) {
            free(session->items[i]->value);
            session->items[i]->value = strdup(value);
            return 0;
        }
    }

    SessionItem *new_item = (SessionItem*)malloc(sizeof(SessionItem));
    new_item->key = strdup(key);
    new_item->value = strdup(value);

    session->count++;
    session->items = (SessionItem**)realloc(session->items, session->count * sizeof(SessionItem*));

    session->items[session->count - 1] = new_item;
    return 0;
}

const char* get_session_item(const Session *session, const char *key) {
    for (size_t i = 0; i < session->count; ++i) {
        if (strcmp(session->items[i]->key, key) == 0) {
            return session->items[i]->value;
        }
    }
    return NULL;
}

void handle_request(Session *session) {
    const char *username = get_session_item(session, SESSION_USERNAME);
    const char *email = get_session_item(session, SESSION_EMAIL);
    const char *ssn = get_session_item(session, SESSION_SSN);

    if (username && email && ssn) {
        printf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        printf("Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        printf("Missing session data.");
    }
}

int main() {
    Session *session = create_session();
    
    // Simulate setting session variables
    set_session_item(session, SESSION_USERNAME, "JohnDoe");
    set_session_item(session, SESSION_EMAIL, "john@example.com");
    set_session_item(session, SESSION_SSN, "123-45-6789");

    // Handle a request to /info
    handle_request(session);

    free_session(session);
    return 0;
}