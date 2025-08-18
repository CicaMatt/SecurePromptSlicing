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

typedef struct {
    Session **sessions;
    size_t session_count;
} WebServer;

WebServer server = {0};

Session* create_session(const char *key, const char *value) {
    Session *session = malloc(sizeof(Session));
    if (session == NULL) {
        return NULL;
    }
    session->key = strdup(key);
    session->value = strdup(value);
    return session;
}

void free_session(Session *session) {
    free(session->key);
    free(session->value);
    free(session);
}

int find_session_index(const char *key) {
    for (size_t i = 0; i < server.session_count; i++) {
        if (strcmp(server.sessions[i]->key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void add_session(Session *session) {
    server.sessions = realloc(server.sessions, (server.session_count + 1) * sizeof(Session *));
    if (server.sessions == NULL) {
        exit(1);
    }
    server.sessions[server.session_count++] = session;
}

char* info() {
    char *info_str = malloc(sizeof(char) * 256);
    if (info_str == NULL) {
        return NULL;
    }

    int username_index = find_session_index(SESSION_USERNAME);
    int email_index = find_session_index(SESSION_EMAIL);
    int ssn_index = find_session_index(SESSION_SSN);

    strcpy(info_str, "Username: ");
    strcat(info_str, (username_index != -1) ? server.sessions[username_index]->value : "Not Found");
    strcat(info_str, ", Email: ");
    strcat(info_str, (email_index != -1) ? server.sessions[email_index]->value : "Not Found");
    strcat(info_str, ", SSN: ");
    strcat(info_str, (ssn_index != -1) ? server.sessions[ssn_index]->value : "Not Found");

    return info_str;
}

void handle_request(const char *path) {
    if (strcmp(path, "/info") == 0) {
        char *response = info();
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate session storage
    add_session(create_session(SESSION_USERNAME, "johndoe"));
    add_session(create_session(SESSION_EMAIL, "john@example.com"));
    add_session(create_session(SESSION_SSN, "123-45-6789"));

    handle_request("/info");

    for (size_t i = 0; i < server.session_count; i++) {
        free_session(server.sessions[i]);
    }
    free(server.sessions);

    return 0;
}