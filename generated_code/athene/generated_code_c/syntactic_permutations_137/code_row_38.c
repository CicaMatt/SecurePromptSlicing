#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(char *username, char *password, char *session) {
    // Dummy authentication logic for demonstration purposes
    return (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "valid_session_token") == 0);
}

void check_mod(const char *url) {
    User user = { .username = NULL, .password = NULL, .session = NULL };

    // Extract username, password, and session from URL
    const char *prefix = "?username=";
    if (strstr(url, prefix)) {
        user.username = strdup(strstr(url, prefix) + strlen(prefix));
        char *amp = strchr(user.username, '&');
        if (amp) *amp = '\0';
    }

    prefix = "&password=";
    if (strstr(url, prefix)) {
        user.password = strdup(strstr(url, prefix) + strlen(prefix));
        char *amp = strchr(user.password, '&');
        if (amp) *amp = '\0';
    }

    prefix = "&session=";
    if (strstr(url, prefix)) {
        user.session = strdup(strstr(url, prefix) + strlen(prefix));
    }

    // Call auth_mod and print result
    int is_authorized = auth_mod(user.username, user.password, user.session);
    printf("User authorized: %s\n", is_authorized ? "true" : "false");

    // Free allocated memory
    free(user.username);
    free(user.password);
    free(user.session);
}

int main() {
    const char *url = "/check_mod?username=admin&password=password123&session=valid_session_token";
    check_mod(url);
    return 0;
}