#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return (strcmp(username, "moderator") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0);
}

void check_mod(const char *url) {
    const char *username = strstr(url, "username=");
    const char *password = strstr(url, "password=");
    const char *session = strstr(url, "session=");

    if (username && password && session) {
        username += strlen("username=");
        password += strlen("password=");
        session += strlen("session=");

        // Find the next '&' to get the actual values
        char *end;
        end = strchr(username, '&');
        if (end) *end = '\0';

        end = strchr(password, '&');
        if (end) *end = '\0';

        end = strchr(session, '&');
        if (end) *end = '\0';

        if (auth_mod(username, password, session)) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL parameters.\n");
    }
}

int main() {
    const char *url = "http://example.com/check_mod?username=moderator&password=secret&session=valid_session";
    check_mod(url);
    return 0;
}