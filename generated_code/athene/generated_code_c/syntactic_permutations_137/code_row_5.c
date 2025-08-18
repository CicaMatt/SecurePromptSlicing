#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(char *username, char *password, char *session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(username, "mod") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "123456") == 0) {
        return 1;
    }
    return 0;
}

void check_mod(const char *url) {
    User user = { .username = NULL, .password = NULL, .session = NULL };
    
    // Parse URL for username, password, and session
    const char *prefix = "?username=";
    if (strstr(url, prefix)) {
        user.username = strdup(strstr(url, prefix) + strlen(prefix));
        const char *sep = strchr(user.username, '&');
        if (sep) {
            *sep = '\0';
        }
    }

    prefix = "&password=";
    if (strstr(url, prefix)) {
        user.password = strdup(strstr(url, prefix) + strlen(prefix));
        const char *sep = strchr(user.password, '&');
        if (sep) {
            *sep = '\0';
        }
    }

    prefix = "&session=";
    if (strstr(url, prefix)) {
        user.session = strdup(strstr(url, prefix) + strlen(prefix));
    }

    int is_mod = auth_mod(user.username, user.password, user.session);

    printf("Is moderator: %s\n", is_mod ? "true" : "false");

    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char *url = "/check_mod?username=mod&password=secret&session=123456";
    check_mod(url);
    return 0;
}