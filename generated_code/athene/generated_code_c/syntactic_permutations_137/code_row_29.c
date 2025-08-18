#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0 && strcmp(session, "123456") == 0) {
        return 1;
    }
    return 0;
}

int check_mod(const char *url) {
    User user = { .username = NULL, .password = NULL, .session = NULL };
    char *token = strtok((char *)url, "?");
    if (token != NULL) {
        while ((token = strtok(NULL, "&")) != NULL) {
            char *key = strtok(token, "=");
            char *value = strtok(NULL, "=");
            if (value == NULL) continue;
            if (strcmp(key, "username") == 0) user.username = value;
            else if (strcmp(key, "password") == 0) user.password = value;
            else if (strcmp(key, "session") == 0) user.session = value;
        }
    }

    if (user.username != NULL && user.password != NULL && user.session != NULL) {
        return auth_mod(user.username, user.password, user.session);
    }

    return 0;
}

int main() {
    const char *url = "/check_mod?username=mod&password=pass&session=123456";
    int is_moderator = check_mod(url);
    printf("Is moderator: %d\n", is_moderator);
    return 0;
}