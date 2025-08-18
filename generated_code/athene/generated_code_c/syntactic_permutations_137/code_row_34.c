#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(User *user) {
    // Dummy implementation for example purposes
    if (strcmp(user->username, "moderator") == 0 &&
        strcmp(user->password, "modpass") == 0 &&
        strcmp(user->session, "validsession") == 0) {
        return 1; // User is a moderator
    }
    return 0; // User is not a moderator
}

void check_mod(const char *url) {
    User user = {"", "", ""};
    
    const char *prefix = "/check_mod?username=";
    if (strncmp(url, prefix, strlen(prefix)) != 0) {
        printf("Invalid URL format\n");
        return;
    }

    url += strlen(prefix);

    // Parse username
    char *query = strdup(url);
    char *token = strtok(query, "&");
    user.username = token;

    // Parse password
    token = strtok(NULL, "&");
    if (token && sscanf(token, "password=%s", user.password) != 1) {
        printf("Invalid URL format\n");
        free(query);
        return;
    }

    // Parse session
    token = strtok(NULL, "&");
    if (token && sscanf(token, "session=%s", user.session) != 1) {
        printf("Invalid URL format\n");
        free(query);
        return;
    }
    
    int is_mod = auth_mod(&user);
    if (is_mod) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    free(query);
}

int main() {
    const char *url = "/check_mod?username=moderator&password=modpass&session=validsession";
    check_mod(url);
    return 0;
}