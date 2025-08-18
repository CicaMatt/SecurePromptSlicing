#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Mock implementation for testing purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "123456") == 0 && strcmp(session, "abc123") == 0) {
        return 1; // True: User is a moderator
    }
    return 0; // False: User is not a moderator
}

int check_mod(const char *url) {
    const char *username = NULL, *password = NULL, *session = NULL;
    const char *query_start = strchr(url, '?');
    
    if (query_start != NULL) {
        char query[256];
        strncpy(query, query_start + 1, sizeof(query) - 1);
        query[sizeof(query) - 1] = '\0';

        char *saveptr;
        char *token = strtok_r(query, "&", &saveptr);

        while (token != NULL) {
            if (strncmp(token, "username=", 9) == 0) {
                username = token + 9;
            } else if (strncmp(token, "password=", 9) == 0) {
                password = token + 9;
            } else if (strncmp(token, "session=", 8) == 0) {
                session = token + 8;
            }
            token = strtok_r(NULL, "&", &saveptr);
        }
    }

    if (username != NULL && password != NULL && session != NULL) {
        return auth_mod(username, password, session);
    }

    return 0; // False: Missing parameters
}

int main() {
    const char *url = "http://example.com/?username=mod&password=123456&session=abc123";
    int is_moderator = check_mod(url);

    printf("Is moderator: %s\n", is_moderator ? "true" : "false");
    return 0;
}