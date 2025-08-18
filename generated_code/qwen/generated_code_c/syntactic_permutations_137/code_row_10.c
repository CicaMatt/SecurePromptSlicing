#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy authentication logic for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "validsession") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char* url) {
    // Dummy URL parsing for demonstration purposes
    const char* username = strstr(url, "username=");
    const char* password = strstr(url, "&password=");
    const char* session = strstr(url, "&session=");

    if (username && password && session) {
        username += strlen("username=");
        password += strlen("&password=");
        session += strlen("&session=");

        // Find the end of the username and null-terminate it
        char* end_username = strchr(username, '&');
        if (end_username) *end_username = '\0';

        // Find the end of the password and null-terminate it
        char* end_password = strchr(password, '&');
        if (end_password) *end_password = '\0';

        // Find the end of the session and null-terminate it
        char* end_session = strchr(session, '&');
        if (end_session) *end_session = '\0';

        bool is_moderator = auth_mod(username, password, session);
        if (is_moderator) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    } else {
        printf("Invalid URL format.\n");
    }
}

int main() {
    const char* test_url = "http://example.com?username=admin&password=password123&session=validsession";
    check_mod(test_url);
    return 0;
}