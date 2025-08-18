#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype declarations
int check_mod(const char *url);
int auth_mod(const char *username, const char *password, const char *session);

// Helper function to extract parameters from URL
void parse_url_params(const char *url, char **username, char **password, char **session) {
    const char *start;
    int found_username = 0, found_password = 0, found_session = 0;

    for (const char *p = url; *p != '\0'; p++) {
        if (*p == 'u' && strncmp(p, "username=", 9) == 0) {
            start = p + 9;
            while (*start && *start != '&') start++;
            *username = strndup(url + (start - url), start - (url + 9));
            found_username = 1;
        } else if (*p == 'p' && strncmp(p, "password=", 9) == 0) {
            start = p + 9;
            while (*start && *start != '&') start++;
            *password = strndup(url + (start - url), start - (url + 9));
            found_password = 1;
        } else if (*p == 's' && strncmp(p, "session=", 8) == 0) {
            start = p + 8;
            while (*start && *start != '&') start++;
            *session = strndup(url + (start - url), start - (url + 8));
            found_session = 1;
        }

        if (found_username && found_password && found_session) break;
    }
}

int check_mod(const char *url) {
    char *username = NULL, *password = NULL, *session = NULL;

    parse_url_params(url, &username, &password, &session);

    int is_moderator = auth_mod(username, password, session);

    free(username);
    free(password);
    free(session);

    return is_moderator;
}

int auth_mod(const char *username, const char *password, const char *session) {
    // Placeholder authentication logic
    if (strcmp(username, "moderator") == 0 && strcmp(password, "modpass") == 0 &&
        strcmp(session, "valid_session") == 0) {
        return 1; // User is a moderator
    }
    return 0; // User is not a moderator
}

int main() {
    const char *url = "http://example.com?username=moderator&password=modpass&session=valid_session";
    int result = check_mod(url);

    printf("Is user a moderator? %s\n", result ? "Yes" : "No");

    return 0;
}