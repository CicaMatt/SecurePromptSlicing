#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "mod") == 0 && strcmp(password, "pass") == 0 && strcmp(session, "1234567890") == 0;
}

void check_mod(const char *url) {
    const char *username = NULL;
    const char *password = NULL;
    const char *session = NULL;

    // Extract parameters from URL
    username = strstr(url, "username=");
    password = strstr(url, "password=");
    session = strstr(url, "session=");

    if (username && password && session) {
        username += 9; // Skip "username="
        password += 9; // Skip "password="
        session += 8;  // Skip "session="

        char *end_username = strchr(username, '&');
        char *end_password = strchr(password, '&');

        if (end_username) *end_username = '\0';
        if (end_password) *end_password = '\0';

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
    const char *url = "http://example.com/check_mod?username=mod&password=pass&session=1234567890";
    check_mod(url);
    return 0;
}